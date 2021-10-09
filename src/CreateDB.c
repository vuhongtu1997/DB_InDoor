/*
 * Author: Thomas Ingleby <thomas.c.ingleby@intel.com>
 * Contributors: Alex Tereschenko <alext.mkrs@gmail.com>
 * Contributors: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 * Copyright (c) 2014 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 *
 * Example usage: Toggles GPIO's 23 and 24 recursively. Press Ctrl+C to exit
 *
 */

/* standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
+
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql, *sql1,*sql2, *sql3,*sql4, *sql5, *sql6, *sql7, *sql8, *sql9, *sql10, *sql11, *sql12, *sql13, *sql14, *sql15, *sql16, *sql17, *sql18, *sql19, *sql20, *sqlQueue;
	const char* data = "";

	//open database
   rc = sqlite3_open("rd.Sqlite", &db);

   //check conect
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   //Create SQL

   sql = "CREATE TABLE IF NOT EXISTS GroupingDeviceMapping ("\
    "GroupingId VACHAR NOT NULL,"\
    "GroupUnicastId INTEGER NOT NULL,"\
    "DeviceId   VACHAR NOT NULL,"\
    "DeviceUnicastId INTEGER NOT NULL,"\
	"IsSuccess INTEGER,"\
    "PRIMARY KEY (GroupingId,DeviceId));";

   sql1 = "CREATE TABLE IF NOT EXISTS DeviceAttributeValue ("\
    "DeviceId        VARCHAR              NOT NULL,"\
    "DeviceUnicastId              INTEGER NOT NULL,"\
    "DeviceAttributeId              INTEGER NOT NULL,"\
    "Value        INTEGER             ,"\
    "UpdateDay        INTEGER             ,"\
	"UpdateTime        INTEGER             ,"\
    "UpdateAt           DATETIME            ,"\
    "PRIMARY KEY ("\
	  "  DeviceId,"\
       " DeviceAttributeId));";

   sql2 = "CREATE TABLE IF NOT EXISTS GROUPING ("\
	"GroupingId       VARCHAR PRIMARY KEY                         NOT NULL,"\
	"GroupUnicastId       INTEGER ,"\
    "Name       VARCHAR (1000) ,"\
    "CategoryId       INTEGER ,"\
    "CreatedAt  DATETIME,"\
    "UpdatedAt  DATETIME,"\
    "DeletedAt  DATETIME);";
//
//   sql11 = "CREATE TABLE IF NOT EXISTS DeviceAttribute ("\
//       "DeviceAttributeID INTEGER        PRIMARY KEY                         NOT NULL,"\
//       "Code       VARCHAR (1000) ,"\
//       "Name  VARCHAR (1000));";

//   "CREATE TABLE IF NOT EXISTS EventTriggerType ("\
//          "EventTriggerTypeId INTEGER        PRIMARY KEY                         NOT NULL,"\
//          "Code       VARCHAR (1000) ,"\
//          "Name  VARCHAR (1000));"\
//		  "insert into EventTriggerType(EventTriggerTypeId, Code, Name) values(1 , 'SCENE', '');"\
//		  "insert into EventTriggerType(EventTriggerTypeId, Code, Name) values(2 , 'RULE', '');";

//   sql12 = "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(0 , 'ONOFF', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(1 , 'DIM', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(2 , 'CCT', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(3 , 'HUE', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(4 , 'SATURATION', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(5 , 'LIGHTNESS', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(6 , 'SONG', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(7 , 'BLINK_MODE', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(8 , 'BATTERY', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(9 , 'LUX', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(10 , 'PIR', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(11 , 'BUTTON_1', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(12 , 'BUTTON_2', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(13 , 'BUTTON_3', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(14 , 'BUTTON_4', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(15 , 'BUTTON_5', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(16 , 'BUTTON_6', '');"\
//		   "insert or replace into DeviceAttribute(DeviceAttributeID, Code, Name) values(17 , 'ACTIME', '');";

   sql20 = "CREATE TABLE IF NOT EXISTS ComparisonOperator ("\
             "CromparisonOperatorId INTEGER        PRIMARY KEY                         NOT NULL,"\
             "Code       VARCHAR (1000) ,"\
             "Name  VARCHAR (1000));"\

		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(1 , 'EQUAL', '=');"\
   		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(2 , 'NOT EQUAL', '!=');"\
   		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(3 , 'LESS', '<');"\
   		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(4 , 'LESS EQUAL', '<=');"\
   		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(5 , 'GREATER', '>');"\
   		   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(6 , 'GREATER EQUAL', '>=');";
   	   	   "insert or replace into ComparisonOperator(ComparisonOperatorId, Code, Name) values(7 , 'MEDIAL', '<<');";



   sql3 = "CREATE TABLE IF NOT EXISTS EventTriggerOutputDeviceMapping ("\
    "EventTriggerId VARCHAR,"\
    "DeviceId VARCHAR ,"\
	"DeviceUnicastId INTEGER ,"\
	"IsSuccess INTEGER,"\
	"typerun    INTEGER,"\
	"PRIMARY KEY ("\
		  "  DeviceId,"\
		  "  typerun,"\
	       " EventTriggerId));";

   sql4 = "CREATE TABLE IF NOT EXISTS EventTriggerOutputGroupingMapping ("\
       "EventTriggerId VARCHAR,"\
       "GroupingId VARCHAR ,"\
	   "GroupUnicastId INTEGER ,"\
	   "typerun    INTEGER,"\
   	"PRIMARY KEY ("\
   		  "  GroupingId,"\
		  "  typerun,"\
   	       " EventTriggerId));";

   sql5 = "CREATE TABLE IF NOT EXISTS EventTriggerOutputDeviceSetupValue ("\
    "EventTriggerId       VARCHAR,"\
    "DeviceId             VARCHAR,"\
	"DeviceUnicastId INTEGER ,"\
    "DeviceAttributeId    INTEGER,"\
    "DeviceAttributeValue INTEGER,"\
	"Time    TIME,"\
	"PRIMARY KEY ("
	   		  "  EventTriggerId,"\
			  "  DeviceId,"\
			  "  Time,"\
	   	       " DeviceAttributeId));";

   sql6 = "CREATE TABLE IF NOT EXISTS EventTriggerOutputGroupingSetupValue ("\
       "EventTriggerId       VARCHAR,"\
       "GroupingId             VARCHAR,"\
	   "GroupUnicastId INTEGER ,"\
       "DeviceAttributeId    INTEGER,"\
       "DeviceAttributeValue INTEGER,"\
	   "Time    TIME,"\
   	    "PRIMARY KEY ("\
   	   		  "  EventTriggerId,"\
   			  "  GroupingId,"\
			  "  Time,"\
   	   	       " DeviceAttributeId));";

   sql7 = "CREATE TABLE IF NOT EXISTS EventTrigger ("\
    "EventTriggerId        VARCHAR PRIMARY KEY NOT NULL,"\
    "GroupId               INTEGER,"\
    "EventTriggerTypeId    BIGINT,"\
	"SceneUnicastID INTEGER,"\
    "Priority              BIGINT,"\
    "Name                  VARCHAR,"\
	"LogicalOperatorID           INTEGER,"\
    "HasTimer              INTEGER,"\
    "StartAt               TIME,"\
    "EndAt                 TIME,"\
	"ValueCreate       INTEGER ,"\
	"StatusID       INTEGER ,"\
    "HasRepeater           INTEGER,"\
    "EachMonday            INTEGER,"\
    "EachTuesday           INTEGER,"\
    "EachWednesday         INTEGER,"\
    "EachThursday          INTEGER,"\
    "EachFriday            INTEGER,"\
    "EachSaturday          INTEGER,"\
    "EachSunday            INTEGER,"\
    "NotificationUsed      INTEGER,"\
	"FADE_IN      INTEGER,"\
    "NotificationDelayTime INTEGER);";


   sql13 = "CREATE TABLE IF NOT EXISTS Device ("\
       "DeviceId        VARCHAR  NOT NULL,"\
       "DeviceUnicastId  INTEGER  NOT NULL,"\
       "AppKey    VARCHAR,"\
       "NetKey              VARCHAR,"\
       "DeviceKey                  VARCHAR,"\
	   "DeviceTypeId                  INTEGER,"\
       "MacAddress                    VARCHAR,"\
       "FirmwareVersion             VARCHAR,"\
	   "UpdateDay                  INTEGER,"\
	   "UpdateTime                  INTEGER,"\
       "StatusId              INTEGER,"\
       "NetworkTypeId      INTEGER,"\
       "CategoryId         INTEGER,"\
       "Owner INTEGER, PRIMARY KEY (DeviceId));";

   sql14 = "CREATE TABLE IF NOT EXISTS GROUPID ("\
    "GroupUnicastId INTEGER,"\
    "GroupingId     VARCHAR,"\
    "ValueCreate    INTEGER,"\
	"IsSuccess INTEGER,"\
	"PRIMARY KEY ("\
	  "  GroupUnicastId));";

   sql15 = "CREATE TABLE IF NOT EXISTS EventTriggerID ("\
       "SceneUnicastID INTEGER,"\
       "EventTriggerId     VARCHAR,"\
       "ValueCreate    INTEGER,"\
	   "IsSuccess INTEGER,"\
	   "PRIMARY KEY ("\
	   	  "  SceneUnicastID));";


   sql16 = "CREATE TABLE IF NOT EXISTS EventTriggerInputDeviceMapping ("\
   "EventTriggerId VARCHAR,"\
   "DeviceId VARCHAR ,"\
   	"DeviceUnicastId INTEGER ,"\
   	"PRIMARY KEY ("\
   		  "  DeviceId,"\
   	       " EventTriggerId));";

   sql17 = "CREATE TABLE IF NOT EXISTS EventTriggerInputGroupingMapping ("\
	  "EventTriggerId VARCHAR,"\
	  "GroupingId VARCHAR ,"\
   	   "GroupUnicastId INTEGER ,"\
	   "PRIMARY KEY ("\
      		  "  GroupingId,"\
      	       " EventTriggerId));";


   sql18 = "CREATE TABLE IF NOT EXISTS EventTriggerInputDeviceSetupValue ("\
       "EventTriggerId       VARCHAR,"\
       "DeviceId             VARCHAR,"\
   	    "DeviceUnicastId INTEGER ,"\
       "DeviceAttributeId    INTEGER,"\
       "ComparisonOperatorId    INTEGER,"\
       "DeviceAttributeValue INTEGER,"\
	   "DeviceAttributeValueMAX INTEGER,"\
   	"PRIMARY KEY ("\
   	   		  "  EventTriggerId,"\
   			  "  DeviceId,"\
   	   	       " DeviceAttributeId));";
   sql19 = "CREATE TABLE IF NOT EXISTS EventTriggerOutputSceneMapping ("\
         "EventTriggerId VARCHAR,"\
         "SceneId VARCHAR ,"\
  	     "SceneUnicastId INTEGER ,"\
		 "Time    TIME,"\
     	"PRIMARY KEY ("\
     		  "  SceneId,"\
			  "  Time,"\
     	       " EventTriggerId));";
   sqlQueue = "CREATE TABLE IF NOT EXISTS QueueMsgRsp ("\
       "RqId VARCHAR NOT NULL,"\
       "Msg     VARCHAR NOT NULL,"\
	   "PRIMARY KEY (RqId));";

   // char *standardControl      = "CREATE TABLE StandardControl(StandardControlId INTEGER NOT NULL, Name VARCHAR,PRIMARY KEY (StandardControlId))";
    char *IrFanAttributeValue     = "CREATE TABLE IF NOT EXISTS IrDeviceAttributeValue(IrDeviceId VARCHAR NOT NULL, IrDeviceUnicastId INTEGER,\
     StandardControlId INTEGER, StandardControlValue INTERGER, IrDeviceAttributeValue INTEGER, DeviceAttributeId INTEGER NOT NULL, DeviceAttributeValueExtension INTEGER, \
     DeviceId VARCHAR , DeviceUnicastId INTEGER, PRIMARY KEY (IrDeviceId, DeviceAttributeId))";
    char *StandardControl  = "CREATE TABLE IF NOT EXISTS StandardControl(StandardControlId INTEGER NOT NULL, Code INTEGER NOT NULL, Name INTEGER NOT NULL,PRIMARY KEY (StandardControlId))";
    char *SystemConfiguration = "CREATE TABLE IF NOT EXISTS SystemConfiguration ("\
    							"Id INTEGER NOT NULL,"\
								"IsConnect VARCHAR,"\
								"DisconnectTime DATETIME,"\
								"ReconnectTime DATETIME,"\
								"IsSync VARCHAR,"\
								"CreateAt DATETIME,"\
								"UpdateAt DATETIME,"\
								"PRIMARY KEY (Id));";

   /* Execute SQL statement */
   int i =1;
    if(sqlite3_exec(db, sql,  callback, (void*)data, &zErrMsg) != SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql1, callback, (void*)data, &zErrMsg) != SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg) != SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql3, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql4, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql5, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql6, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql7, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
//    i++;
//    if(sqlite3_exec(db, sql11, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
//        printf("%d\n",i);
//        return 0;
//    }
//    i++;
//    if(sqlite3_exec(db, sql12, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
//        printf("%d\n",i);
//        return 0;
//    }
    i++;
    if(sqlite3_exec(db, sql13, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql14, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql15, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql16, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql17, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql18, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, sql19, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
    if(sqlite3_exec(db, IrFanAttributeValue, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
        printf("%d\n",i);
        return 0;
    }
    i++;
	if(sqlite3_exec(db, StandardControl, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
		printf("%d\n",i);
		return 0;
    }
	i++;
	if(sqlite3_exec(db, SystemConfiguration, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
		printf("%d\n",i);
		return 0;
	}
	i++;
	if(sqlite3_exec(db, sqlQueue, callback, (void*)data, &zErrMsg)!= SQLITE_OK){
		printf("%d\n",i);
		return 0;
	}
    puts("DONE!!!");
    sqlite3_close(db);
   return 0;
}


#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_12__ {int /*<<< orphan*/  pSqllogArg; int /*<<< orphan*/  (* xSqllog ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int /*<<< orphan*/  SQLITE_MAGIC_ZOMBIE ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ connectionIsBusy (TYPE_1__*) ; 
 int /*<<< orphan*/  disconnectAllVtab (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_1__*,int,char*) ; 
 TYPE_6__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3LeaveMutexAndCloseZombie (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckSickOrOk (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VtabRollback (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sqlite3Close(sqlite3 *db, int forceZombie){
  if( !db ){
    return SQLITE_OK;
  }
  if( !sqlite3SafetyCheckSickOrOk(db) ){
    return SQLITE_MISUSE_BKPT;
  }
  sqlite3_mutex_enter(db->mutex);

  /* Force xDisconnect calls on all virtual tables */
  disconnectAllVtab(db);

  /* If a transaction is open, the disconnectAllVtab() call above
  ** will not have called the xDisconnect() method on any virtual
  ** tables in the db->aVTrans[] array. The following sqlite3VtabRollback()
  ** call will do so. We need to do this before the check for active
  ** SQL statements below, as the v-table implementation may be storing
  ** some prepared statements internally.
  */
  sqlite3VtabRollback(db);

  /* Legacy behavior (sqlite3_close() behavior) is to return
  ** SQLITE_BUSY if the connection can not be closed immediately.
  */
  if( !forceZombie && connectionIsBusy(db) ){
    sqlite3Error(db, SQLITE_BUSY, "unable to close due to unfinalized "
       "statements or unfinished backups");
    sqlite3_mutex_leave(db->mutex);
    return SQLITE_BUSY;
  }

#ifdef SQLITE_ENABLE_SQLLOG
  if( sqlite3GlobalConfig.xSqllog ){
    /* Closing the handle. Fourth parameter is passed the value 2. */
    sqlite3GlobalConfig.xSqllog(sqlite3GlobalConfig.pSqllogArg, db, 0, 2);
  }
#endif

  /* Convert the connection into a zombie and then close it.
  */
  db->magic = SQLITE_MAGIC_ZOMBIE;
  sqlite3LeaveMutexAndCloseZombie(db);
  return SQLITE_OK;
}
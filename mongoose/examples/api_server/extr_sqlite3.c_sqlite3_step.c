#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mallocFailed; int /*<<< orphan*/  pErr; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_10__ {int doingRerun; scalar_t__ expired; int rc; int /*<<< orphan*/  zErrMsg; int /*<<< orphan*/  isPrepareV2; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 scalar_t__ ALWAYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_MAX_SCHEMA_RETRY ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_SCHEMA ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbStrDup (TYPE_1__*,char const*) ; 
 int sqlite3Reprepare (TYPE_2__*) ; 
 int sqlite3Step (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ ) ; 
 scalar_t__ vdbeSafetyNotNull (TYPE_2__*) ; 

int sqlite3_step(sqlite3_stmt *pStmt){
  int rc = SQLITE_OK;      /* Result from sqlite3Step() */
  int rc2 = SQLITE_OK;     /* Result from sqlite3Reprepare() */
  Vdbe *v = (Vdbe*)pStmt;  /* the prepared statement */
  int cnt = 0;             /* Counter to prevent infinite loop of reprepares */
  sqlite3 *db;             /* The database connection */

  if( vdbeSafetyNotNull(v) ){
    return SQLITE_MISUSE_BKPT;
  }
  db = v->db;
  sqlite3_mutex_enter(db->mutex);
  v->doingRerun = 0;
  while( (rc = sqlite3Step(v))==SQLITE_SCHEMA
         && cnt++ < SQLITE_MAX_SCHEMA_RETRY
         && (rc2 = rc = sqlite3Reprepare(v))==SQLITE_OK ){
    sqlite3_reset(pStmt);
    v->doingRerun = 1;
    assert( v->expired==0 );
  }
  if( rc2!=SQLITE_OK && ALWAYS(v->isPrepareV2) && ALWAYS(db->pErr) ){
    /* This case occurs after failing to recompile an sql statement. 
    ** The error message from the SQL compiler has already been loaded 
    ** into the database handle. This block copies the error message 
    ** from the database handle into the statement and sets the statement
    ** program counter to 0 to ensure that when the statement is 
    ** finalized or reset the parser error message is available via
    ** sqlite3_errmsg() and sqlite3_errcode().
    */
    const char *zErr = (const char *)sqlite3_value_text(db->pErr); 
    sqlite3DbFree(db, v->zErrMsg);
    if( !db->mallocFailed ){
      v->zErrMsg = sqlite3DbStrDup(db, zErr);
      v->rc = rc2;
    } else {
      v->zErrMsg = 0;
      v->rc = rc = SQLITE_NOMEM;
    }
  }
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}
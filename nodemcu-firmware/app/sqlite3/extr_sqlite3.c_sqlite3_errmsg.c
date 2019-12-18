#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pErr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  errCode; scalar_t__ mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int /*<<< orphan*/  SQLITE_NOMEM_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 char const* sqlite3ErrStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckSickOrOk (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 

const char *sqlite3_errmsg(sqlite3 *db){
  const char *z;
  if( !db ){
    return sqlite3ErrStr(SQLITE_NOMEM_BKPT);
  }
  if( !sqlite3SafetyCheckSickOrOk(db) ){
    return sqlite3ErrStr(SQLITE_MISUSE_BKPT);
  }
  sqlite3_mutex_enter(db->mutex);
  if( db->mallocFailed ){
    z = sqlite3ErrStr(SQLITE_NOMEM_BKPT);
  }else{
    testcase( db->pErr==0 );
    z = (char*)sqlite3_value_text(db->pErr);
    assert( !db->mallocFailed );
    if( z==0 ){
      z = sqlite3ErrStr(db->errCode);
    }
  }
  sqlite3_mutex_leave(db->mutex);
  return z;
}
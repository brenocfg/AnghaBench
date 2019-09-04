#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u16 ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pErr; int /*<<< orphan*/  errCode; scalar_t__ mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorWithMsg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OomClear (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckSickOrOk (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 void* sqlite3_value_text16 (int /*<<< orphan*/ ) ; 

const void *sqlite3_errmsg16(sqlite3 *db){
  static const u16 outOfMem[] = {
    'o', 'u', 't', ' ', 'o', 'f', ' ', 'm', 'e', 'm', 'o', 'r', 'y', 0
  };
  static const u16 misuse[] = {
    'b', 'a', 'd', ' ', 'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', ' ',
    'o', 'r', ' ', 'o', 't', 'h', 'e', 'r', ' ', 'A', 'P', 'I', ' ',
    'm', 'i', 's', 'u', 's', 'e', 0
  };

  const void *z;
  if( !db ){
    return (void *)outOfMem;
  }
  if( !sqlite3SafetyCheckSickOrOk(db) ){
    return (void *)misuse;
  }
  sqlite3_mutex_enter(db->mutex);
  if( db->mallocFailed ){
    z = (void *)outOfMem;
  }else{
    z = sqlite3_value_text16(db->pErr);
    if( z==0 ){
      sqlite3ErrorWithMsg(db, db->errCode, sqlite3ErrStr(db->errCode));
      z = sqlite3_value_text16(db->pErr);
    }
    /* A malloc() may have failed within the call to sqlite3_value_text16()
    ** above. If this is the case, then the db->mallocFailed flag needs to
    ** be cleared before returning. Do this directly, instead of via
    ** sqlite3ApiExit(), to avoid setting the database handle error message.
    */
    sqlite3OomClear(db);
  }
  sqlite3_mutex_leave(db->mutex);
  return z;
}
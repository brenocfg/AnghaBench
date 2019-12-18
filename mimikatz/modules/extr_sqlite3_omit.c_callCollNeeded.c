#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_9__ {int /*<<< orphan*/  pCollNeededArg; int /*<<< orphan*/  (* xCollNeeded16 ) (int /*<<< orphan*/ ,TYPE_1__*,int,char const*) ;int /*<<< orphan*/  (* xCollNeeded ) (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ;} ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 scalar_t__ ENC (TYPE_1__*) ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_UTF16NATIVE ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,char*) ; 
 char* sqlite3DbStrDup (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ValueNew (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ValueSetStr (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sqlite3ValueText (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int,char const*) ; 

__attribute__((used)) static void callCollNeeded(sqlite3 *db, int enc, const char *zName){
  assert( !db->xCollNeeded || !db->xCollNeeded16 );
  if( db->xCollNeeded ){
    char *zExternal = sqlite3DbStrDup(db, zName);
    if( !zExternal ) return;
    db->xCollNeeded(db->pCollNeededArg, db, enc, zExternal);
    sqlite3DbFree(db, zExternal);
  }
#ifndef SQLITE_OMIT_UTF16
  if( db->xCollNeeded16 ){
    char const *zExternal;
    sqlite3_value *pTmp = sqlite3ValueNew(db);
    sqlite3ValueSetStr(pTmp, -1, zName, SQLITE_UTF8, SQLITE_STATIC);
    zExternal = sqlite3ValueText(pTmp, SQLITE_UTF16NATIVE);
    if( zExternal ){
      db->xCollNeeded16(db->pCollNeededArg, db, (int)ENC(db), zExternal);
    }
    sqlite3ValueFree(pTmp);
  }
#endif
}
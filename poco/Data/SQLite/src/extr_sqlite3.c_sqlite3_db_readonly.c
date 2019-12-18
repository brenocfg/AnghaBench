#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int sqlite3BtreeIsReadonly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3DbNameToBtree (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (int /*<<< orphan*/ *) ; 

int sqlite3_db_readonly(sqlite3 *db, const char *zDbName){
  Btree *pBt;
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) ){
    (void)SQLITE_MISUSE_BKPT;
    return -1;
  }
#endif
  pBt = sqlite3DbNameToBtree(db, zDbName);
  return pBt ? sqlite3BtreeIsReadonly(pBt) : -1;
}
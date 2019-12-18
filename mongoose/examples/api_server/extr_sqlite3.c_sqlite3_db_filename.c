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
 char const* sqlite3BtreeGetFilename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3DbNameToBtree (int /*<<< orphan*/ *,char const*) ; 

const char *sqlite3_db_filename(sqlite3 *db, const char *zDbName){
  Btree *pBt = sqlite3DbNameToBtree(db, zDbName);
  return pBt ? sqlite3BtreeGetFilename(pBt) : 0;
}
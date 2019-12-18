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

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,char*) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ *,char*,char*,...) ; 

__attribute__((used)) static char *whereOrName(sqlite3 *db, char *zWhere, char *zConstant){
  char *zNew;
  if( !zWhere ){
    zNew = sqlite3MPrintf(db, "name=%Q", zConstant);
  }else{
    zNew = sqlite3MPrintf(db, "%s OR name=%Q", zWhere, zConstant);
    sqlite3DbFree(db, zWhere);
  }
  return zNew;
}
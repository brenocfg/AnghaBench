#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int nModuleArg; char** azModuleArg; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,char*) ; 
 char** sqlite3DbRealloc (int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static void addModuleArgument(sqlite3 *db, Table *pTable, char *zArg){
  int nBytes = sizeof(char *)*(2+pTable->nModuleArg);
  char **azModuleArg;
  azModuleArg = sqlite3DbRealloc(db, pTable->azModuleArg, nBytes);
  if( azModuleArg==0 ){
    sqlite3DbFree(db, zArg);
  }else{
    int i = pTable->nModuleArg++;
    azModuleArg[i] = zArg;
    azModuleArg[i+1] = 0;
    pTable->azModuleArg = azModuleArg;
  }
}
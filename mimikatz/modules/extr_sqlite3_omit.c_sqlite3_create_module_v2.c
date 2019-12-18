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
typedef  int /*<<< orphan*/  sqlite3_module ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int createModule (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,void*,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (int /*<<< orphan*/ *) ; 

int sqlite3_create_module_v2(
  sqlite3 *db,                    /* Database in which module is registered */
  const char *zName,              /* Name assigned to this module */
  const sqlite3_module *pModule,  /* The definition of the module */
  void *pAux,                     /* Context pointer for xCreate/xConnect */
  void (*xDestroy)(void *)        /* Module destructor function */
){
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) || zName==0 ) return SQLITE_MISUSE_BKPT;
#endif
  return createModule(db, zName, pModule, pAux, xDestroy);
}
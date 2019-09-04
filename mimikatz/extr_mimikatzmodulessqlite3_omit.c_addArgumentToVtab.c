#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int n; scalar_t__ z; } ;
struct TYPE_5__ {scalar_t__ pNewTable; int /*<<< orphan*/ * db; TYPE_1__ sArg; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  addModuleArgument (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbStrNDup (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void addArgumentToVtab(Parse *pParse){
  if( pParse->sArg.z && pParse->pNewTable ){
    const char *z = (const char*)pParse->sArg.z;
    int n = pParse->sArg.n;
    sqlite3 *db = pParse->db;
    addModuleArgument(db, pParse->pNewTable, sqlite3DbStrNDup(db, z, n));
  }
}
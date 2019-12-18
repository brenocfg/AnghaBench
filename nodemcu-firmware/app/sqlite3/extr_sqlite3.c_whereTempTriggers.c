#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_16__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  const* pSchema; struct TYPE_16__* pNext; } ;
typedef  TYPE_3__ Trigger ;
struct TYPE_17__ {int /*<<< orphan*/  const* pSchema; } ;
typedef  TYPE_4__ Table ;
struct TYPE_18__ {TYPE_2__* db; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pSchema; } ;
typedef  int /*<<< orphan*/  Schema ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char*) ; 
 char* sqlite3MPrintf (TYPE_2__*,char*,char*) ; 
 TYPE_3__* sqlite3TriggerList (TYPE_5__*,TYPE_4__*) ; 
 char* whereOrName (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *whereTempTriggers(Parse *pParse, Table *pTab){
  Trigger *pTrig;
  char *zWhere = 0;
  const Schema *pTempSchema = pParse->db->aDb[1].pSchema; /* Temp db schema */

  /* If the table is not located in the temp-db (in which case NULL is
  ** returned, loop through the tables list of triggers. For each trigger
  ** that is not part of the temp-db schema, add a clause to the WHERE
  ** expression being built up in zWhere.
  */
  if( pTab->pSchema!=pTempSchema ){
    sqlite3 *db = pParse->db;
    for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
      if( pTrig->pSchema==pTempSchema ){
        zWhere = whereOrName(db, zWhere, pTrig->zName);
      }
    }
  }
  if( zWhere ){
    char *zNew = sqlite3MPrintf(pParse->db, "type='trigger' AND (%s)", zWhere);
    sqlite3DbFree(pParse->db, zWhere);
    zWhere = zNew;
  }
  return zWhere;
}
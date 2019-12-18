#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
struct TYPE_6__ {int /*<<< orphan*/  pRename; int /*<<< orphan*/  zErrMsg; int /*<<< orphan*/  pNewTrigger; TYPE_2__* pNewIndex; int /*<<< orphan*/  pNewTable; scalar_t__ pVdbe; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  renameTokenFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DeleteTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DeleteTrigger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3FreeIndex (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ParserReset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFinalize (scalar_t__) ; 

__attribute__((used)) static void renameParseCleanup(Parse *pParse){
  sqlite3 *db = pParse->db;
  Index *pIdx;
  if( pParse->pVdbe ){
    sqlite3VdbeFinalize(pParse->pVdbe);
  }
  sqlite3DeleteTable(db, pParse->pNewTable);
  while( (pIdx = pParse->pNewIndex)!=0 ){
    pParse->pNewIndex = pIdx->pNext;
    sqlite3FreeIndex(db, pIdx);
  }
  sqlite3DeleteTrigger(db, pParse->pNewTrigger);
  sqlite3DbFree(db, pParse->zErrMsg);
  renameTokenFree(db, pParse->pRename);
  sqlite3ParserReset(pParse);
}
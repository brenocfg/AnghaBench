#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_14__ {struct TYPE_14__* pNextLoop; } ;
typedef  TYPE_4__ WhereLoop ;
struct TYPE_12__ {int /*<<< orphan*/  aInLoop; } ;
struct TYPE_13__ {TYPE_2__ in; } ;
struct TYPE_15__ {TYPE_3__ u; TYPE_1__* pWLoop; } ;
typedef  TYPE_5__ WhereLevel ;
struct TYPE_16__ {int nLevel; TYPE_4__* pLoops; int /*<<< orphan*/  sWC; TYPE_5__* a; } ;
typedef  TYPE_6__ WhereInfo ;
struct TYPE_11__ {int wsFlags; } ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_6__*) ; 
 int WHERE_IN_ABLE ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3WhereClauseClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whereLoopDelete (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void whereInfoFree(sqlite3 *db, WhereInfo *pWInfo){
  if( ALWAYS(pWInfo) ){
    int i;
    for(i=0; i<pWInfo->nLevel; i++){
      WhereLevel *pLevel = &pWInfo->a[i];
      if( pLevel->pWLoop && (pLevel->pWLoop->wsFlags & WHERE_IN_ABLE) ){
        sqlite3DbFree(db, pLevel->u.in.aInLoop);
      }
    }
    sqlite3WhereClauseClear(&pWInfo->sWC);
    while( pWInfo->pLoops ){
      WhereLoop *p = pWInfo->pLoops;
      pWInfo->pLoops = p->pNextLoop;
      whereLoopDelete(db, p);
    }
    sqlite3DbFreeNN(db, pWInfo);
  }
}
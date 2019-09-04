#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_7__ {struct TYPE_7__* pPrior; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pEList; TYPE_2__* pSrc; } ;
struct TYPE_6__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_5__ {int /*<<< orphan*/  pOn; TYPE_3__* pSelect; } ;
typedef  TYPE_2__ SrcList ;
typedef  TYPE_3__ Select ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int /*<<< orphan*/  sqlite3WhereExprListUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WhereExprUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bitmask exprSelectUsage(WhereMaskSet *pMaskSet, Select *pS){
  Bitmask mask = 0;
  while( pS ){
    SrcList *pSrc = pS->pSrc;
    mask |= sqlite3WhereExprListUsage(pMaskSet, pS->pEList);
    mask |= sqlite3WhereExprListUsage(pMaskSet, pS->pGroupBy);
    mask |= sqlite3WhereExprListUsage(pMaskSet, pS->pOrderBy);
    mask |= sqlite3WhereExprUsage(pMaskSet, pS->pWhere);
    mask |= sqlite3WhereExprUsage(pMaskSet, pS->pHaving);
    if( ALWAYS(pSrc!=0) ){
      int i;
      for(i=0; i<pSrc->nSrc; i++){
        mask |= exprSelectUsage(pMaskSet, pSrc->a[i].pSelect);
        mask |= sqlite3WhereExprUsage(pMaskSet, pSrc->a[i].pOn);
      }
    }
    pS = pS->pPrior;
  }
  return mask;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pLimit; int selFlags; scalar_t__ op; int nSelectRow; struct TYPE_6__* pNext; struct TYPE_6__* pPrior; TYPE_1__* pEList; } ;
struct TYPE_5__ {scalar_t__ nExpr; } ;
typedef  int /*<<< orphan*/  SelectDest ;
typedef  TYPE_2__ Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainQueryPlan (int /*<<< orphan*/ *) ; 
 int SF_MultiValue ; 
 int SF_Values ; 
 scalar_t__ TK_ALL ; 
 scalar_t__ TK_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  selectInnerLoop (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int multiSelectValues(
  Parse *pParse,        /* Parsing context */
  Select *p,            /* The right-most of SELECTs to be coded */
  SelectDest *pDest     /* What to do with query results */
){
  int nRow = 1;
  int rc = 0;
  int bShowAll = p->pLimit==0;
  assert( p->selFlags & SF_MultiValue );
  do{
    assert( p->selFlags & SF_Values );
    assert( p->op==TK_ALL || (p->op==TK_SELECT && p->pPrior==0) );
    assert( p->pNext==0 || p->pEList->nExpr==p->pNext->pEList->nExpr );
    if( p->pPrior==0 ) break;
    assert( p->pPrior->pNext==p );
    p = p->pPrior;
    nRow += bShowAll;
  }while(1);
  ExplainQueryPlan((pParse, 0, "SCAN %d CONSTANT ROW%s", nRow,
                    nRow==1 ? "" : "S"));
  while( p ){
    selectInnerLoop(pParse, p, -1, 0, 0, pDest, 1, 1);
    if( !bShowAll ) break;
    p->nSelectRow = nRow;
    p = p->pNext;
  }
  return rc;
}
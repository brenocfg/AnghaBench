#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ExprList_item {TYPE_1__* pExpr; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_14__ {TYPE_5__* pParse; } ;
typedef  TYPE_3__ Walker ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_16__ {int /*<<< orphan*/ * db; } ;
struct TYPE_15__ {scalar_t__ pPrior; scalar_t__ op; scalar_t__ pOffset; scalar_t__ pLimit; TYPE_2__* pOrderBy; scalar_t__ pHaving; scalar_t__ pGroupBy; scalar_t__ pWhere; int /*<<< orphan*/  pEList; int /*<<< orphan*/ * pSrc; } ;
struct TYPE_13__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_12__ {int flags; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 int EP_Collate ; 
 scalar_t__ TK_ALL ; 
 scalar_t__ TK_SELECT ; 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* sqlite3DbMallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3Expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListAppend (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3SrcListAppendFromTerm (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convertCompoundSelectToSubquery(Walker *pWalker, Select *p){
  int i;
  Select *pNew;
  Select *pX;
  sqlite3 *db;
  struct ExprList_item *a;
  SrcList *pNewSrc;
  Parse *pParse;
  Token dummy;

  if( p->pPrior==0 ) return WRC_Continue;
  if( p->pOrderBy==0 ) return WRC_Continue;
  for(pX=p; pX && (pX->op==TK_ALL || pX->op==TK_SELECT); pX=pX->pPrior){}
  if( pX==0 ) return WRC_Continue;
  a = p->pOrderBy->a;
  for(i=p->pOrderBy->nExpr-1; i>=0; i--){
    if( a[i].pExpr->flags & EP_Collate ) break;
  }
  if( i<0 ) return WRC_Continue;

  /* If we reach this point, that means the transformation is required. */

  pParse = pWalker->pParse;
  db = pParse->db;
  pNew = sqlite3DbMallocZero(db, sizeof(*pNew) );
  if( pNew==0 ) return WRC_Abort;
  memset(&dummy, 0, sizeof(dummy));
  pNewSrc = sqlite3SrcListAppendFromTerm(pParse,0,0,0,&dummy,pNew,0,0);
  if( pNewSrc==0 ) return WRC_Abort;
  *pNew = *p;
  p->pSrc = pNewSrc;
  p->pEList = sqlite3ExprListAppend(pParse, 0, sqlite3Expr(db, TK_ALL, 0));
  p->op = TK_SELECT;
  p->pWhere = 0;
  pNew->pGroupBy = 0;
  pNew->pHaving = 0;
  pNew->pOrderBy = 0;
  p->pPrior = 0;
  pNew->pLimit = 0;
  pNew->pOffset = 0;
  return WRC_Continue;
}
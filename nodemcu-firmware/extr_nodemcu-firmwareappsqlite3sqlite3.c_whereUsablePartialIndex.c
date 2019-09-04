#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* pExpr; } ;
typedef  TYPE_1__ WhereTerm ;
struct TYPE_10__ {int nTerm; TYPE_1__* a; } ;
typedef  TYPE_2__ WhereClause ;
struct TYPE_11__ {scalar_t__ op; int iRightJoinTable; struct TYPE_11__* pRight; struct TYPE_11__* pLeft; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_AND ; 
 scalar_t__ sqlite3ExprImpliesExpr (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static int whereUsablePartialIndex(int iTab, WhereClause *pWC, Expr *pWhere){
  int i;
  WhereTerm *pTerm;
  while( pWhere->op==TK_AND ){
    if( !whereUsablePartialIndex(iTab,pWC,pWhere->pLeft) ) return 0;
    pWhere = pWhere->pRight;
  }
  for(i=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    Expr *pExpr = pTerm->pExpr;
    if( sqlite3ExprImpliesExpr(pExpr, pWhere, iTab)
     && (!ExprHasProperty(pExpr, EP_FromJoin) || pExpr->iRightJoinTable==iTab)
    ){
      return 1;
    }
  }
  return 0;
}
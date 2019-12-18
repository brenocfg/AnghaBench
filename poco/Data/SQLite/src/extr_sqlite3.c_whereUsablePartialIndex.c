#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* pExpr; } ;
typedef  TYPE_3__ WhereTerm ;
struct TYPE_16__ {int nTerm; TYPE_3__* a; TYPE_1__* pWInfo; } ;
typedef  TYPE_4__ WhereClause ;
struct TYPE_18__ {scalar_t__ op; int iRightJoinTable; struct TYPE_18__* pRight; struct TYPE_18__* pLeft; } ;
struct TYPE_17__ {TYPE_2__* db; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {TYPE_5__* pParse; } ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int SQLITE_EnableQPSG ; 
 scalar_t__ TK_AND ; 
 scalar_t__ sqlite3ExprImpliesExpr (TYPE_5__*,TYPE_6__*,TYPE_6__*,int) ; 

__attribute__((used)) static int whereUsablePartialIndex(int iTab, WhereClause *pWC, Expr *pWhere){
  int i;
  WhereTerm *pTerm;
  Parse *pParse = pWC->pWInfo->pParse;
  while( pWhere->op==TK_AND ){
    if( !whereUsablePartialIndex(iTab,pWC,pWhere->pLeft) ) return 0;
    pWhere = pWhere->pRight;
  }
  if( pParse->db->flags & SQLITE_EnableQPSG ) pParse = 0;
  for(i=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    Expr *pExpr = pTerm->pExpr;
    if( (!ExprHasProperty(pExpr, EP_FromJoin) || pExpr->iRightJoinTable==iTab)
     && sqlite3ExprImpliesExpr(pParse, pExpr, pWhere, iTab) 
    ){
      return 1;
    }
  }
  return 0;
}
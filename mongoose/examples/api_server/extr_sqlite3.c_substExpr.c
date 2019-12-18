#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_14__ {int /*<<< orphan*/  pList; int /*<<< orphan*/  pSelect; } ;
struct TYPE_16__ {scalar_t__ op; int iTable; size_t iColumn; TYPE_2__ x; struct TYPE_16__* pRight; struct TYPE_16__* pLeft; } ;
struct TYPE_15__ {size_t nExpr; TYPE_1__* a; } ;
struct TYPE_13__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_3__ ExprList ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ TK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* sqlite3ExprDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substExprList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  substSelect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static Expr *substExpr(
  sqlite3 *db,        /* Report malloc errors to this connection */
  Expr *pExpr,        /* Expr in which substitution occurs */
  int iTable,         /* Table to be substituted */
  ExprList *pEList    /* Substitute expressions */
){
  if( pExpr==0 ) return 0;
  if( pExpr->op==TK_COLUMN && pExpr->iTable==iTable ){
    if( pExpr->iColumn<0 ){
      pExpr->op = TK_NULL;
    }else{
      Expr *pNew;
      assert( pEList!=0 && pExpr->iColumn<pEList->nExpr );
      assert( pExpr->pLeft==0 && pExpr->pRight==0 );
      pNew = sqlite3ExprDup(db, pEList->a[pExpr->iColumn].pExpr, 0);
      sqlite3ExprDelete(db, pExpr);
      pExpr = pNew;
    }
  }else{
    pExpr->pLeft = substExpr(db, pExpr->pLeft, iTable, pEList);
    pExpr->pRight = substExpr(db, pExpr->pRight, iTable, pEList);
    if( ExprHasProperty(pExpr, EP_xIsSelect) ){
      substSelect(db, pExpr->x.pSelect, iTable, pEList);
    }else{
      substExprList(db, pExpr->x.pList, iTable, pEList);
    }
  }
  return pExpr;
}
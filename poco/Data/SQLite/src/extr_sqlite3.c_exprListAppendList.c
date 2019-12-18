#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ op; int flags; } ;
struct TYPE_16__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_15__ {int /*<<< orphan*/  db; } ;
struct TYPE_14__ {int /*<<< orphan*/  sortOrder; int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ ExprList ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int EP_IntValue ; 
 int EP_IsFalse ; 
 int EP_IsTrue ; 
 scalar_t__ TK_INTEGER ; 
 scalar_t__ TK_NULL ; 
 TYPE_4__* sqlite3ExprDup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sqlite3ExprListAppend (TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static ExprList *exprListAppendList(
  Parse *pParse,          /* Parsing context */
  ExprList *pList,        /* List to which to append. Might be NULL */
  ExprList *pAppend,      /* List of values to append. Might be NULL */
  int bIntToNull
){
  if( pAppend ){
    int i;
    int nInit = pList ? pList->nExpr : 0;
    for(i=0; i<pAppend->nExpr; i++){
      Expr *pDup = sqlite3ExprDup(pParse->db, pAppend->a[i].pExpr, 0);
      if( bIntToNull && pDup && pDup->op==TK_INTEGER ){
        pDup->op = TK_NULL;
        pDup->flags &= ~(EP_IntValue|EP_IsTrue|EP_IsFalse);
      }
      pList = sqlite3ExprListAppend(pParse, pList, pDup);
      if( pList ) pList->a[nInit+i].sortOrder = pAppend->a[i].sortOrder;
    }
  }
  return pList;
}
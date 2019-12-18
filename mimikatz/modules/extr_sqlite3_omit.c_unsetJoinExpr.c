#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pList; } ;
struct TYPE_11__ {int iRightJoinTable; scalar_t__ op; struct TYPE_11__* pRight; struct TYPE_11__* pLeft; TYPE_3__ x; } ;
struct TYPE_9__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_8__ {TYPE_4__* pExpr; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  ExprClearProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_FUNCTION ; 

__attribute__((used)) static void unsetJoinExpr(Expr *p, int iTable){
  while( p ){
    if( ExprHasProperty(p, EP_FromJoin)
     && (iTable<0 || p->iRightJoinTable==iTable) ){
      ExprClearProperty(p, EP_FromJoin);
    }
    if( p->op==TK_FUNCTION && p->x.pList ){
      int i;
      for(i=0; i<p->x.pList->nExpr; i++){
        unsetJoinExpr(p->x.pList->a[i].pExpr, iTable);
      }
    }
    unsetJoinExpr(p->pLeft, iTable);
    p = p->pRight;
  } 
}
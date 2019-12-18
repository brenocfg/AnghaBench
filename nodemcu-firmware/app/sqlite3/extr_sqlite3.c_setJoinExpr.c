#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i16 ;
struct TYPE_11__ {TYPE_2__* pList; } ;
struct TYPE_12__ {scalar_t__ op; struct TYPE_12__* pRight; struct TYPE_12__* pLeft; TYPE_3__ x; scalar_t__ iRightJoinTable; } ;
struct TYPE_10__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_9__ {TYPE_4__* pExpr; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  EP_NoReduce ; 
 int EP_Reduced ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetVVAProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_FUNCTION ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void setJoinExpr(Expr *p, int iTable){
  while( p ){
    ExprSetProperty(p, EP_FromJoin);
    assert( !ExprHasProperty(p, EP_TokenOnly|EP_Reduced) );
    ExprSetVVAProperty(p, EP_NoReduce);
    p->iRightJoinTable = (i16)iTable;
    if( p->op==TK_FUNCTION && p->x.pList ){
      int i;
      for(i=0; i<p->x.pList->nExpr; i++){
        setJoinExpr(p->x.pList->a[i].pExpr, iTable);
      }
    }
    setJoinExpr(p->pLeft, iTable);
    p = p->pRight;
  }
}
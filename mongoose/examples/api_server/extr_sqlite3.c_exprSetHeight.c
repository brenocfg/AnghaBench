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
struct TYPE_5__ {int /*<<< orphan*/  pList; int /*<<< orphan*/  pSelect; } ;
struct TYPE_6__ {int nHeight; TYPE_1__ x; int /*<<< orphan*/  pRight; int /*<<< orphan*/  pLeft; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heightOfExpr (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heightOfExprList (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heightOfSelect (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void exprSetHeight(Expr *p){
  int nHeight = 0;
  heightOfExpr(p->pLeft, &nHeight);
  heightOfExpr(p->pRight, &nHeight);
  if( ExprHasProperty(p, EP_xIsSelect) ){
    heightOfSelect(p->x.pSelect, &nHeight);
  }else{
    heightOfExprList(p->x.pList, &nHeight);
  }
  p->nHeight = nHeight + 1;
}
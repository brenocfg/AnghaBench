#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ eCode; } ;
typedef  TYPE_1__ Walker ;
struct TYPE_7__ {scalar_t__ op; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_ConstFunc ; 
 scalar_t__ ExprHasProperty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_FUNCTION ; 
 int WRC_Abort ; 
 int WRC_Continue ; 

__attribute__((used)) static int exprNodeIsDeterministic(Walker *pWalker, Expr *pExpr){
  if( pExpr->op==TK_FUNCTION && ExprHasProperty(pExpr, EP_ConstFunc)==0 ){
    pWalker->eCode = 0;
    return WRC_Abort;
  }
  return WRC_Continue;
}
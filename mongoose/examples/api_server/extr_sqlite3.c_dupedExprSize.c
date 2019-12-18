#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* pRight; struct TYPE_4__* pLeft; } ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int EXPRDUP_REDUCE ; 
 int dupedExprNodeSize (TYPE_1__*,int) ; 

__attribute__((used)) static int dupedExprSize(Expr *p, int flags){
  int nByte = 0;
  if( p ){
    nByte = dupedExprNodeSize(p, flags);
    if( flags&EXPRDUP_REDUCE ){
      nByte += dupedExprSize(p->pLeft, flags) + dupedExprSize(p->pRight, flags);
    }
  }
  return nByte;
}
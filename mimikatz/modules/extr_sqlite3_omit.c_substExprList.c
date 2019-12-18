#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_4__ {int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  SubstContext ;
typedef  TYPE_2__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  substExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void substExprList(
  SubstContext *pSubst, /* Description of the substitution */
  ExprList *pList       /* List to scan and in which to make substitutes */
){
  int i;
  if( pList==0 ) return;
  for(i=0; i<pList->nExpr; i++){
    pList->a[i].pExpr = substExpr(pSubst, pList->a[i].pExpr);
  }
}
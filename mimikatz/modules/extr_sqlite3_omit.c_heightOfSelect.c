#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pEList; int /*<<< orphan*/  pLimit; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pWhere; struct TYPE_3__* pPrior; } ;
typedef  TYPE_1__ Select ;

/* Variables and functions */
 int /*<<< orphan*/  heightOfExpr (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heightOfExprList (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void heightOfSelect(Select *pSelect, int *pnHeight){
  Select *p;
  for(p=pSelect; p; p=p->pPrior){
    heightOfExpr(p->pWhere, pnHeight);
    heightOfExpr(p->pHaving, pnHeight);
    heightOfExpr(p->pLimit, pnHeight);
    heightOfExprList(p->pEList, pnHeight);
    heightOfExprList(p->pGroupBy, pnHeight);
    heightOfExprList(p->pOrderBy, pnHeight);
  }
}
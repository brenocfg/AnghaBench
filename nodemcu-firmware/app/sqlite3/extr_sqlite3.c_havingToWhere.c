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
struct HavingToWhereCtx {int /*<<< orphan*/ * pGroupBy; int /*<<< orphan*/ ** ppWhere; } ;
typedef  int /*<<< orphan*/  sWalker ;
struct TYPE_5__ {struct HavingToWhereCtx* pHavingCtx; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  havingToWhereExprCb ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void havingToWhere(
  Parse *pParse,
  ExprList *pGroupBy,
  Expr *pHaving,
  Expr **ppWhere
){
  struct HavingToWhereCtx sCtx;
  Walker sWalker;

  sCtx.ppWhere = ppWhere;
  sCtx.pGroupBy = pGroupBy;

  memset(&sWalker, 0, sizeof(sWalker));
  sWalker.pParse = pParse;
  sWalker.xExprCallback = havingToWhereExprCb;
  sWalker.u.pHavingCtx = &sCtx;
  sqlite3WalkExpr(&sWalker, pHaving);
}
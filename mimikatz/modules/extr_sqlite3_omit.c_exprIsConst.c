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
struct TYPE_4__ {int iCur; } ;
struct TYPE_5__ {int eCode; TYPE_1__ u; int /*<<< orphan*/  xSelectCallback2; int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  exprNodeIsConstant ; 
 int /*<<< orphan*/  sqlite3SelectWalkAssert2 ; 
 int /*<<< orphan*/  sqlite3SelectWalkFail ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exprIsConst(Expr *p, int initFlag, int iCur){
  Walker w;
  w.eCode = initFlag;
  w.xExprCallback = exprNodeIsConstant;
  w.xSelectCallback = sqlite3SelectWalkFail;
#ifdef SQLITE_DEBUG
  w.xSelectCallback2 = sqlite3SelectWalkAssert2;
#endif
  w.u.iCur = iCur;
  sqlite3WalkExpr(&w, p);
  return w.eCode;
}
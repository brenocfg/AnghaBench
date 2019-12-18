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
struct TYPE_4__ {scalar_t__ op; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 scalar_t__ TK_SELECT ; 
 int sqlite3CodeSubselect (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int exprCodeSubselect(Parse *pParse, Expr *pExpr){
  int reg = 0;
#ifndef SQLITE_OMIT_SUBQUERY
  if( pExpr->op==TK_SELECT ){
    reg = sqlite3CodeSubselect(pParse, pExpr);
  }
#endif
  return reg;
}
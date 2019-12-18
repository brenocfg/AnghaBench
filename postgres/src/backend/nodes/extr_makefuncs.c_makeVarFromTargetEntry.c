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
typedef  int /*<<< orphan*/  Var ;
struct TYPE_3__ {scalar_t__ expr; int /*<<< orphan*/  resno; } ;
typedef  TYPE_1__ TargetEntry ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprTypmod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Var *
makeVarFromTargetEntry(Index varno,
					   TargetEntry *tle)
{
	return makeVar(varno,
				   tle->resno,
				   exprType((Node *) tle->expr),
				   exprTypmod((Node *) tle->expr),
				   exprCollation((Node *) tle->expr),
				   0);
}
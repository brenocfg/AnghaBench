#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ExprState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReadyInterpretedExpr (int /*<<< orphan*/ *) ; 
 scalar_t__ jit_compile_expr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExecReadyExpr(ExprState *state)
{
	if (jit_compile_expr(state))
		return;

	ExecReadyInterpretedExpr(state);
}
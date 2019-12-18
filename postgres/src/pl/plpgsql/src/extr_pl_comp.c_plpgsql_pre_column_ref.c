#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* func; } ;
struct TYPE_8__ {scalar_t__ p_ref_hook_state; } ;
struct TYPE_7__ {scalar_t__ resolve_option; } ;
typedef  TYPE_2__ ParseState ;
typedef  TYPE_3__ PLpgSQL_expr ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  ColumnRef ;

/* Variables and functions */
 scalar_t__ PLPGSQL_RESOLVE_VARIABLE ; 
 int /*<<< orphan*/ * resolve_column_ref (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Node *
plpgsql_pre_column_ref(ParseState *pstate, ColumnRef *cref)
{
	PLpgSQL_expr *expr = (PLpgSQL_expr *) pstate->p_ref_hook_state;

	if (expr->func->resolve_option == PLPGSQL_RESOLVE_VARIABLE)
		return resolve_column_ref(pstate, expr, cref, false);
	else
		return NULL;
}
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
struct TYPE_9__ {int number; int /*<<< orphan*/  location; } ;
struct TYPE_8__ {int /*<<< orphan*/  p_ref_hook_state; } ;
struct TYPE_7__ {int nargs; } ;
typedef  TYPE_1__* SQLFunctionParseInfoPtr ;
typedef  TYPE_2__ ParseState ;
typedef  TYPE_3__ ParamRef ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * sql_fn_make_param (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
sql_fn_param_ref(ParseState *pstate, ParamRef *pref)
{
	SQLFunctionParseInfoPtr pinfo = (SQLFunctionParseInfoPtr) pstate->p_ref_hook_state;
	int			paramno = pref->number;

	/* Check parameter number is valid */
	if (paramno <= 0 || paramno > pinfo->nargs)
		return NULL;			/* unknown parameter number */

	return sql_fn_make_param(pinfo, paramno, pref->location);
}
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
struct TYPE_4__ {scalar_t__* numParams; } ;
typedef  TYPE_1__ VarParamState ;
struct TYPE_5__ {scalar_t__ p_ref_hook_state; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_2__ ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  check_parameter_resolution_walker ; 
 int /*<<< orphan*/  query_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
check_variable_parameters(ParseState *pstate, Query *query)
{
	VarParamState *parstate = (VarParamState *) pstate->p_ref_hook_state;

	/* If numParams is zero then no Params were generated, so no work */
	if (*parstate->numParams > 0)
		(void) query_tree_walker(query,
								 check_parameter_resolution_walker,
								 (void *) pstate, 0);
}
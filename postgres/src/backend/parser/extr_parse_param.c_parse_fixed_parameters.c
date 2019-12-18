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
struct TYPE_6__ {int numParams; int /*<<< orphan*/ * paramTypes; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_paramref_hook; void* p_ref_hook_state; } ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FixedParamState ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_paramref_hook ; 
 TYPE_2__* palloc (int) ; 

void
parse_fixed_parameters(ParseState *pstate,
					   Oid *paramTypes, int numParams)
{
	FixedParamState *parstate = palloc(sizeof(FixedParamState));

	parstate->paramTypes = paramTypes;
	parstate->numParams = numParams;
	pstate->p_ref_hook_state = (void *) parstate;
	pstate->p_paramref_hook = fixed_paramref_hook;
	/* no need to use p_coerce_param_hook */
}
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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IsPolymorphicType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enforce_generic_type_consistency (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_func_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

Oid
resolve_aggregate_transtype(Oid aggfuncid,
							Oid aggtranstype,
							Oid *inputTypes,
							int numArguments)
{
	/* resolve actual type of transition state, if polymorphic */
	if (IsPolymorphicType(aggtranstype))
	{
		/* have to fetch the agg's declared input types... */
		Oid		   *declaredArgTypes;
		int			agg_nargs;

		(void) get_func_signature(aggfuncid, &declaredArgTypes, &agg_nargs);

		/*
		 * VARIADIC ANY aggs could have more actual than declared args, but
		 * such extra args can't affect polymorphic type resolution.
		 */
		Assert(agg_nargs <= numArguments);

		aggtranstype = enforce_generic_type_consistency(inputTypes,
														declaredArgTypes,
														agg_nargs,
														aggtranstype,
														false);
		pfree(declaredArgTypes);
	}
	return aggtranstype;
}
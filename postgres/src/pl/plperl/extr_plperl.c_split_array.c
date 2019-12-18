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
struct TYPE_4__ {int ndims; int* nelems; } ;
typedef  TYPE_1__ plperl_array_info ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ * make_array_ref (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SV  *
split_array(plperl_array_info *info, int first, int last, int nest)
{
	dTHX;
	int			i;
	AV		   *result;

	/* we should only be called when we have something to split */
	Assert(info->ndims > 0);

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	/*
	 * Base case, return a reference to a single-dimensional array
	 */
	if (nest >= info->ndims - 1)
		return make_array_ref(info, first, last);

	result = newAV();
	for (i = first; i < last; i += info->nelems[nest + 1])
	{
		/* Recursively form references to arrays of lower dimensions */
		SV		   *ref = split_array(info, i, i + info->nelems[nest + 1], nest + 1);

		av_push(result, ref);
	}
	return newRV_noinc((SV *) result);
}
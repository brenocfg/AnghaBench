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
struct TYPE_3__ {int max_hazard; char max_interesting; } ;
typedef  TYPE_1__ max_parallel_hazard_context ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
#define  PROPARALLEL_RESTRICTED 130 
#define  PROPARALLEL_SAFE 129 
#define  PROPARALLEL_UNSAFE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char) ; 

__attribute__((used)) static bool
max_parallel_hazard_test(char proparallel, max_parallel_hazard_context *context)
{
	switch (proparallel)
	{
		case PROPARALLEL_SAFE:
			/* nothing to see here, move along */
			break;
		case PROPARALLEL_RESTRICTED:
			/* increase max_hazard to RESTRICTED */
			Assert(context->max_hazard != PROPARALLEL_UNSAFE);
			context->max_hazard = proparallel;
			/* done if we are not expecting any unsafe functions */
			if (context->max_interesting == proparallel)
				return true;
			break;
		case PROPARALLEL_UNSAFE:
			context->max_hazard = proparallel;
			/* we're always done at the first unsafe construct */
			return true;
		default:
			elog(ERROR, "unrecognized proparallel value \"%c\"", proparallel);
			break;
	}
	return false;
}
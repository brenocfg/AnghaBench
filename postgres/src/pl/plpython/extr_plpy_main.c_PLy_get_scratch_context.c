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
struct TYPE_3__ {int /*<<< orphan*/ * scratch_ctx; } ;
typedef  TYPE_1__ PLyExecutionContext ;
typedef  int /*<<< orphan*/ * MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopTransactionContext ; 

MemoryContext
PLy_get_scratch_context(PLyExecutionContext *context)
{
	/*
	 * A scratch context might never be needed in a given plpython procedure,
	 * so allocate it on first request.
	 */
	if (context->scratch_ctx == NULL)
		context->scratch_ctx =
			AllocSetContextCreate(TopTransactionContext,
								  "PL/Python scratch context",
								  ALLOCSET_DEFAULT_SIZES);
	return context->scratch_ctx;
}
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
typedef  scalar_t__ XactEvent ;

/* Variables and functions */
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 scalar_t__ XACT_EVENT_ABORT ; 
 scalar_t__ XACT_EVENT_COMMIT ; 
 scalar_t__ XACT_EVENT_PREPARE ; 
 int /*<<< orphan*/ * shared_simple_eval_estate ; 
 int /*<<< orphan*/ * simple_econtext_stack ; 

void
plpgsql_xact_cb(XactEvent event, void *arg)
{
	/*
	 * If we are doing a clean transaction shutdown, free the EState (so that
	 * any remaining resources will be released correctly). In an abort, we
	 * expect the regular abort recovery procedures to release everything of
	 * interest.
	 */
	if (event == XACT_EVENT_COMMIT || event == XACT_EVENT_PREPARE)
	{
		simple_econtext_stack = NULL;

		if (shared_simple_eval_estate)
			FreeExecutorState(shared_simple_eval_estate);
		shared_simple_eval_estate = NULL;
	}
	else if (event == XACT_EVENT_ABORT)
	{
		simple_econtext_stack = NULL;
		shared_simple_eval_estate = NULL;
	}
}
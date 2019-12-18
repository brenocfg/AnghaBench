#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * head; } ;
struct TYPE_4__ {int query_depth; scalar_t__ maxquerydepth; scalar_t__ maxtransdepth; int /*<<< orphan*/ * trans_stack; TYPE_1__ events; int /*<<< orphan*/ * event_cxt; int /*<<< orphan*/ * query_stack; int /*<<< orphan*/ * state; scalar_t__ firing_counter; } ;
typedef  scalar_t__ CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__ afterTriggers ; 

void
AfterTriggerBeginXact(void)
{
	/*
	 * Initialize after-trigger state structure to empty
	 */
	afterTriggers.firing_counter = (CommandId) 1;	/* mustn't be 0 */
	afterTriggers.query_depth = -1;

	/*
	 * Verify that there is no leftover state remaining.  If these assertions
	 * trip, it means that AfterTriggerEndXact wasn't called or didn't clean
	 * up properly.
	 */
	Assert(afterTriggers.state == NULL);
	Assert(afterTriggers.query_stack == NULL);
	Assert(afterTriggers.maxquerydepth == 0);
	Assert(afterTriggers.event_cxt == NULL);
	Assert(afterTriggers.events.head == NULL);
	Assert(afterTriggers.trans_stack == NULL);
	Assert(afterTriggers.maxtransdepth == 0);
}
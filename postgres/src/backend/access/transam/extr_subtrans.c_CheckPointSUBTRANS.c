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

/* Variables and functions */
 int /*<<< orphan*/  SimpleLruFlush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SubTransCtl ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SUBTRANS_CHECKPOINT_DONE (int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SUBTRANS_CHECKPOINT_START (int) ; 

void
CheckPointSUBTRANS(void)
{
	/*
	 * Flush dirty SUBTRANS pages to disk
	 *
	 * This is not actually necessary from a correctness point of view. We do
	 * it merely to improve the odds that writing of dirty pages is done by
	 * the checkpoint process and not by backends.
	 */
	TRACE_POSTGRESQL_SUBTRANS_CHECKPOINT_START(true);
	SimpleLruFlush(SubTransCtl, true);
	TRACE_POSTGRESQL_SUBTRANS_CHECKPOINT_DONE(true);
}
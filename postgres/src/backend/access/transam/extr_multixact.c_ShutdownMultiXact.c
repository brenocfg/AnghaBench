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
 int /*<<< orphan*/  MultiXactMemberCtl ; 
 int /*<<< orphan*/  MultiXactOffsetCtl ; 
 int /*<<< orphan*/  SimpleLruFlush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_MULTIXACT_CHECKPOINT_DONE (int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_MULTIXACT_CHECKPOINT_START (int) ; 

void
ShutdownMultiXact(void)
{
	/* Flush dirty MultiXact pages to disk */
	TRACE_POSTGRESQL_MULTIXACT_CHECKPOINT_START(false);
	SimpleLruFlush(MultiXactOffsetCtl, false);
	SimpleLruFlush(MultiXactMemberCtl, false);
	TRACE_POSTGRESQL_MULTIXACT_CHECKPOINT_DONE(false);
}
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
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  LISTEN_LISTEN ; 
 int /*<<< orphan*/  MyProcPid ; 
 scalar_t__ Trace_notify ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_listen (int /*<<< orphan*/ ,char const*) ; 

void
Async_Listen(const char *channel)
{
	if (Trace_notify)
		elog(DEBUG1, "Async_Listen(%s,%d)", channel, MyProcPid);

	queue_listen(LISTEN_LISTEN, channel);
}
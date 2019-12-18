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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MAX_BACKENDS ; 
 scalar_t__ MaxBackends ; 
 scalar_t__ MaxConnections ; 
 scalar_t__ autovacuum_max_workers ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ max_wal_senders ; 
 scalar_t__ max_worker_processes ; 

void
InitializeMaxBackends(void)
{
	Assert(MaxBackends == 0);

	/* the extra unit accounts for the autovacuum launcher */
	MaxBackends = MaxConnections + autovacuum_max_workers + 1 +
		max_worker_processes + max_wal_senders;

	/* internal error because the values were all checked previously */
	if (MaxBackends > MAX_BACKENDS)
		elog(ERROR, "too many backends configured");
}
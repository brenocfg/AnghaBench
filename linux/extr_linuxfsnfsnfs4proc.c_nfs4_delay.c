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
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freezable_schedule_timeout_killable_unsafe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nfs4_update_delay (long*) ; 

__attribute__((used)) static int nfs4_delay(struct rpc_clnt *clnt, long *timeout)
{
	int res = 0;

	might_sleep();

	freezable_schedule_timeout_killable_unsafe(
		nfs4_update_delay(timeout));
	if (fatal_signal_pending(current))
		res = -ERESTARTSYS;
	return res;
}
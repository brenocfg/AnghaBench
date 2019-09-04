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
struct rds_conn_path {int /*<<< orphan*/  cp_waitq; int /*<<< orphan*/  cp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_IN_XMIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_in_xmit(struct rds_conn_path *cp)
{
	clear_bit(RDS_IN_XMIT, &cp->cp_flags);
	smp_mb__after_atomic();
	/*
	 * We don't use wait_on_bit()/wake_up_bit() because our waking is in a
	 * hot path and finding waiters is very rare.  We don't want to walk
	 * the system-wide hashed waitqueue buckets in the fast path only to
	 * almost never find waiters.
	 */
	if (waitqueue_active(&cp->cp_waitq))
		wake_up_all(&cp->cp_waitq);
}
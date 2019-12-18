#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  send_flags; } ;
struct rds_ib_send_work {TYPE_1__ s_wr; } ;
struct rds_ib_connection {scalar_t__ i_unsignaled_wrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 scalar_t__ rds_ib_sysctl_max_unsig_wrs ; 

__attribute__((used)) static inline int rds_ib_set_wr_signal_state(struct rds_ib_connection *ic,
					     struct rds_ib_send_work *send,
					     bool notify)
{
	/*
	 * We want to delay signaling completions just enough to get
	 * the batching benefits but not so much that we create dead time
	 * on the wire.
	 */
	if (ic->i_unsignaled_wrs-- == 0 || notify) {
		ic->i_unsignaled_wrs = rds_ib_sysctl_max_unsig_wrs;
		send->s_wr.send_flags |= IB_SEND_SIGNALED;
		return 1;
	}
	return 0;
}
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
typedef  scalar_t__ u32 ;
struct cnic_sock {scalar_t__ context; } ;
struct bnx2i_endpoint {scalar_t__ state; scalar_t__ conn; int /*<<< orphan*/  hba; int /*<<< orphan*/  ofld_wait; } ;

/* Variables and functions */
 scalar_t__ EP_STATE_DISCONN_START ; 
 scalar_t__ EP_STATE_TCP_RST_RCVD ; 
 int /*<<< orphan*/  bnx2i_recovery_que_add_conn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_cm_remote_abort(struct cnic_sock *cm_sk)
{
	struct bnx2i_endpoint *ep = (struct bnx2i_endpoint *) cm_sk->context;
	u32 old_state = ep->state;

	ep->state = EP_STATE_TCP_RST_RCVD;
	if (old_state == EP_STATE_DISCONN_START)
		wake_up_interruptible(&ep->ofld_wait);
	else
		if (ep->conn)
			bnx2i_recovery_que_add_conn(ep->hba, ep->conn);
}
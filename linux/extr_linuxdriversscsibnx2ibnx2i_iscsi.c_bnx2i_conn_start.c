#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_conn {struct bnx2i_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct bnx2i_conn {TYPE_1__* ep; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {scalar_t__ state; TYPE_2__ ofld_timer; int /*<<< orphan*/  ofld_wait; } ;

/* Variables and functions */
 scalar_t__ EP_STATE_ULP_UPDATE_START ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  bnx2i_ep_ofld_timer ; 
 int /*<<< orphan*/  bnx2i_update_iscsi_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_start (struct iscsi_cls_conn*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2i_conn_start(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct bnx2i_conn *bnx2i_conn = conn->dd_data;

	bnx2i_conn->ep->state = EP_STATE_ULP_UPDATE_START;
	bnx2i_update_iscsi_conn(conn);

	/*
	 * this should normally not sleep for a long time so it should
	 * not disrupt the caller.
	 */
	timer_setup(&bnx2i_conn->ep->ofld_timer, bnx2i_ep_ofld_timer, 0);
	bnx2i_conn->ep->ofld_timer.expires = 1 * HZ + jiffies;
	add_timer(&bnx2i_conn->ep->ofld_timer);
	/* update iSCSI context for this conn, wait for CNIC to complete */
	wait_event_interruptible(bnx2i_conn->ep->ofld_wait,
			bnx2i_conn->ep->state != EP_STATE_ULP_UPDATE_START);

	if (signal_pending(current))
		flush_signals(current);
	del_timer_sync(&bnx2i_conn->ep->ofld_timer);

	iscsi_conn_start(cls_conn);
	return 0;
}
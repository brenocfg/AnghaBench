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
struct ceph_mon_client {int cur_mon; int /*<<< orphan*/  monmap; int /*<<< orphan*/  m_subscribe_ack; int /*<<< orphan*/  m_subscribe; int /*<<< orphan*/  m_auth_reply; int /*<<< orphan*/  m_auth; int /*<<< orphan*/  generic_request_tree; int /*<<< orphan*/  auth; int /*<<< orphan*/  mutex; int /*<<< orphan*/  delayed_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __close_session (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_auth_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msgr_flush () ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ceph_monc_stop(struct ceph_mon_client *monc)
{
	dout("stop\n");
	cancel_delayed_work_sync(&monc->delayed_work);

	mutex_lock(&monc->mutex);
	__close_session(monc);
	monc->cur_mon = -1;
	mutex_unlock(&monc->mutex);

	/*
	 * flush msgr queue before we destroy ourselves to ensure that:
	 *  - any work that references our embedded con is finished.
	 *  - any osd_client or other work that may reference an authorizer
	 *    finishes before we shut down the auth subsystem.
	 */
	ceph_msgr_flush();

	ceph_auth_destroy(monc->auth);

	WARN_ON(!RB_EMPTY_ROOT(&monc->generic_request_tree));

	ceph_msg_put(monc->m_auth);
	ceph_msg_put(monc->m_auth_reply);
	ceph_msg_put(monc->m_subscribe);
	ceph_msg_put(monc->m_subscribe_ack);

	kfree(monc->monmap);
}
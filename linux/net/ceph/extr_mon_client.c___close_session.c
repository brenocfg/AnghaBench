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
struct ceph_mon_client {int /*<<< orphan*/  auth; scalar_t__ pending_auth; int /*<<< orphan*/  con; int /*<<< orphan*/  m_subscribe_ack; int /*<<< orphan*/  m_subscribe; int /*<<< orphan*/  m_auth_reply; int /*<<< orphan*/  m_auth; int /*<<< orphan*/  cur_mon; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_auth_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_con_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_msg_revoke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_revoke_incoming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __close_session(struct ceph_mon_client *monc)
{
	dout("__close_session closing mon%d\n", monc->cur_mon);
	ceph_msg_revoke(monc->m_auth);
	ceph_msg_revoke_incoming(monc->m_auth_reply);
	ceph_msg_revoke(monc->m_subscribe);
	ceph_msg_revoke_incoming(monc->m_subscribe_ack);
	ceph_con_close(&monc->con);

	monc->pending_auth = 0;
	ceph_auth_reset(monc->auth);
}
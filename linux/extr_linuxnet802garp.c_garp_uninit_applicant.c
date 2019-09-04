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
struct net_device {int /*<<< orphan*/  garp_port; } ;
struct garp_port {int /*<<< orphan*/ * applicants; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_address; } ;
struct garp_application {size_t type; TYPE_1__ proto; } ;
struct garp_applicant {int /*<<< orphan*/  lock; int /*<<< orphan*/  join_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  GARP_EVENT_TRANSMIT_PDU ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_gid_event (struct garp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_pdu_queue (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_queue_xmit (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_release_port (struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct garp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void garp_uninit_applicant(struct net_device *dev, struct garp_application *appl)
{
	struct garp_port *port = rtnl_dereference(dev->garp_port);
	struct garp_applicant *app = rtnl_dereference(port->applicants[appl->type]);

	ASSERT_RTNL();

	RCU_INIT_POINTER(port->applicants[appl->type], NULL);

	/* Delete timer and generate a final TRANSMIT_PDU event to flush out
	 * all pending messages before the applicant is gone. */
	del_timer_sync(&app->join_timer);

	spin_lock_bh(&app->lock);
	garp_gid_event(app, GARP_EVENT_TRANSMIT_PDU);
	garp_pdu_queue(app);
	spin_unlock_bh(&app->lock);

	garp_queue_xmit(app);

	dev_mc_del(dev, appl->proto.group_address);
	kfree_rcu(app, rcu);
	garp_release_port(dev);
}
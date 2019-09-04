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
struct net_device {int /*<<< orphan*/  mrp_port; } ;
struct mrp_port {int /*<<< orphan*/ * applicants; } ;
struct mrp_application {size_t type; int /*<<< orphan*/  group_address; } ;
struct mrp_applicant {int /*<<< orphan*/  lock; int /*<<< orphan*/  periodic_timer; int /*<<< orphan*/  join_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  MRP_EVENT_TX ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct mrp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrp_mad_event (struct mrp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrp_pdu_queue (struct mrp_applicant*) ; 
 int /*<<< orphan*/  mrp_queue_xmit (struct mrp_applicant*) ; 
 int /*<<< orphan*/  mrp_release_port (struct net_device*) ; 
 int /*<<< orphan*/  rcu ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mrp_uninit_applicant(struct net_device *dev, struct mrp_application *appl)
{
	struct mrp_port *port = rtnl_dereference(dev->mrp_port);
	struct mrp_applicant *app = rtnl_dereference(
		port->applicants[appl->type]);

	ASSERT_RTNL();

	RCU_INIT_POINTER(port->applicants[appl->type], NULL);

	/* Delete timer and generate a final TX event to flush out
	 * all pending messages before the applicant is gone.
	 */
	del_timer_sync(&app->join_timer);
	del_timer_sync(&app->periodic_timer);

	spin_lock_bh(&app->lock);
	mrp_mad_event(app, MRP_EVENT_TX);
	mrp_pdu_queue(app);
	spin_unlock_bh(&app->lock);

	mrp_queue_xmit(app);

	dev_mc_del(dev, appl->group_address);
	kfree_rcu(app, rcu);
	mrp_release_port(dev);
}
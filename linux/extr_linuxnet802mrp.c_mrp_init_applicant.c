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
struct net_device {TYPE_1__* mrp_port; } ;
struct mrp_application {size_t type; int /*<<< orphan*/  group_address; } ;
struct mrp_applicant {int /*<<< orphan*/  periodic_timer; int /*<<< orphan*/  join_timer; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  mad; struct mrp_application* app; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * applicants; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int dev_mc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mrp_applicant*) ; 
 struct mrp_applicant* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mrp_init_port (struct net_device*) ; 
 int /*<<< orphan*/  mrp_join_timer ; 
 int /*<<< orphan*/  mrp_join_timer_arm (struct mrp_applicant*) ; 
 int /*<<< orphan*/  mrp_periodic_timer ; 
 int /*<<< orphan*/  mrp_periodic_timer_arm (struct mrp_applicant*) ; 
 int /*<<< orphan*/  mrp_release_port (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct mrp_applicant*) ; 
 int /*<<< orphan*/  rtnl_dereference (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mrp_init_applicant(struct net_device *dev, struct mrp_application *appl)
{
	struct mrp_applicant *app;
	int err;

	ASSERT_RTNL();

	if (!rtnl_dereference(dev->mrp_port)) {
		err = mrp_init_port(dev);
		if (err < 0)
			goto err1;
	}

	err = -ENOMEM;
	app = kzalloc(sizeof(*app), GFP_KERNEL);
	if (!app)
		goto err2;

	err = dev_mc_add(dev, appl->group_address);
	if (err < 0)
		goto err3;

	app->dev = dev;
	app->app = appl;
	app->mad = RB_ROOT;
	spin_lock_init(&app->lock);
	skb_queue_head_init(&app->queue);
	rcu_assign_pointer(dev->mrp_port->applicants[appl->type], app);
	timer_setup(&app->join_timer, mrp_join_timer, 0);
	mrp_join_timer_arm(app);
	timer_setup(&app->periodic_timer, mrp_periodic_timer, 0);
	mrp_periodic_timer_arm(app);
	return 0;

err3:
	kfree(app);
err2:
	mrp_release_port(dev);
err1:
	return err;
}
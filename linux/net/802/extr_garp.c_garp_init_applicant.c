#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_2__* garp_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  group_address; } ;
struct garp_application {size_t type; TYPE_1__ proto; } ;
struct garp_applicant {int /*<<< orphan*/  join_timer; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  gid; struct garp_application* app; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * applicants; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int dev_mc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int garp_init_port (struct net_device*) ; 
 int /*<<< orphan*/  garp_join_timer ; 
 int /*<<< orphan*/  garp_join_timer_arm (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_release_port (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct garp_applicant*) ; 
 struct garp_applicant* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct garp_applicant*) ; 
 int /*<<< orphan*/  rtnl_dereference (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int garp_init_applicant(struct net_device *dev, struct garp_application *appl)
{
	struct garp_applicant *app;
	int err;

	ASSERT_RTNL();

	if (!rtnl_dereference(dev->garp_port)) {
		err = garp_init_port(dev);
		if (err < 0)
			goto err1;
	}

	err = -ENOMEM;
	app = kzalloc(sizeof(*app), GFP_KERNEL);
	if (!app)
		goto err2;

	err = dev_mc_add(dev, appl->proto.group_address);
	if (err < 0)
		goto err3;

	app->dev = dev;
	app->app = appl;
	app->gid = RB_ROOT;
	spin_lock_init(&app->lock);
	skb_queue_head_init(&app->queue);
	rcu_assign_pointer(dev->garp_port->applicants[appl->type], app);
	timer_setup(&app->join_timer, garp_join_timer, 0);
	garp_join_timer_arm(app);
	return 0;

err3:
	kfree(app);
err2:
	garp_release_port(dev);
err1:
	return err;
}
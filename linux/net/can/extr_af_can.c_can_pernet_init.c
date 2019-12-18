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
struct TYPE_3__ {TYPE_2__* rx_alldev_list; TYPE_2__* pkg_stats; int /*<<< orphan*/  stattimer; void* rcv_lists_stats; int /*<<< orphan*/  rcvlists_lock; } ;
struct net {TYPE_1__ can; } ;
struct TYPE_4__ {scalar_t__ jiffies_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PROC_FS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_init_proc (struct net*) ; 
 int /*<<< orphan*/  can_stat_update ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stats_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int can_pernet_init(struct net *net)
{
	spin_lock_init(&net->can.rcvlists_lock);
	net->can.rx_alldev_list =
		kzalloc(sizeof(*net->can.rx_alldev_list), GFP_KERNEL);
	if (!net->can.rx_alldev_list)
		goto out;
	net->can.pkg_stats = kzalloc(sizeof(*net->can.pkg_stats), GFP_KERNEL);
	if (!net->can.pkg_stats)
		goto out_free_rx_alldev_list;
	net->can.rcv_lists_stats = kzalloc(sizeof(*net->can.rcv_lists_stats), GFP_KERNEL);
	if (!net->can.rcv_lists_stats)
		goto out_free_pkg_stats;

	if (IS_ENABLED(CONFIG_PROC_FS)) {
		/* the statistics are updated every second (timer triggered) */
		if (stats_timer) {
			timer_setup(&net->can.stattimer, can_stat_update,
				    0);
			mod_timer(&net->can.stattimer,
				  round_jiffies(jiffies + HZ));
		}
		net->can.pkg_stats->jiffies_init = jiffies;
		can_init_proc(net);
	}

	return 0;

 out_free_pkg_stats:
	kfree(net->can.pkg_stats);
 out_free_rx_alldev_list:
	kfree(net->can.rx_alldev_list);
 out:
	return -ENOMEM;
}
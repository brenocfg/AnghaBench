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
struct s_stats {int dummy; } ;
struct s_pstats {int dummy; } ;
struct TYPE_3__ {TYPE_2__* can_rx_alldev_list; TYPE_2__* can_stats; int /*<<< orphan*/  can_stattimer; void* can_pstats; int /*<<< orphan*/  can_rcvlists_lock; } ;
struct net {TYPE_1__ can; } ;
struct can_dev_rcv_lists {int dummy; } ;
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
	spin_lock_init(&net->can.can_rcvlists_lock);
	net->can.can_rx_alldev_list =
		kzalloc(sizeof(struct can_dev_rcv_lists), GFP_KERNEL);
	if (!net->can.can_rx_alldev_list)
		goto out;
	net->can.can_stats = kzalloc(sizeof(struct s_stats), GFP_KERNEL);
	if (!net->can.can_stats)
		goto out_free_alldev_list;
	net->can.can_pstats = kzalloc(sizeof(struct s_pstats), GFP_KERNEL);
	if (!net->can.can_pstats)
		goto out_free_can_stats;

	if (IS_ENABLED(CONFIG_PROC_FS)) {
		/* the statistics are updated every second (timer triggered) */
		if (stats_timer) {
			timer_setup(&net->can.can_stattimer, can_stat_update,
				    0);
			mod_timer(&net->can.can_stattimer,
				  round_jiffies(jiffies + HZ));
		}
		net->can.can_stats->jiffies_init = jiffies;
		can_init_proc(net);
	}

	return 0;

 out_free_can_stats:
	kfree(net->can.can_stats);
 out_free_alldev_list:
	kfree(net->can.can_rx_alldev_list);
 out:
	return -ENOMEM;
}
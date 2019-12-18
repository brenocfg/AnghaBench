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
struct TYPE_2__ {int /*<<< orphan*/  rcv_lists_stats; int /*<<< orphan*/  pkg_stats; int /*<<< orphan*/  rx_alldev_list; int /*<<< orphan*/  stattimer; } ;
struct net {TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PROC_FS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_remove_proc (struct net*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ stats_timer ; 

__attribute__((used)) static void can_pernet_exit(struct net *net)
{
	if (IS_ENABLED(CONFIG_PROC_FS)) {
		can_remove_proc(net);
		if (stats_timer)
			del_timer_sync(&net->can.stattimer);
	}

	kfree(net->can.rx_alldev_list);
	kfree(net->can.pkg_stats);
	kfree(net->can.rcv_lists_stats);
}
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
struct TYPE_2__ {struct can_rcv_lists_stats* rcv_lists_stats; struct can_pkg_stats* pkg_stats; } ;
struct net {TYPE_1__ can; } ;
struct can_rcv_lists_stats {int /*<<< orphan*/  user_reset; int /*<<< orphan*/  stats_reset; } ;
struct can_pkg_stats {int /*<<< orphan*/  jiffies_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct can_pkg_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ user_reset ; 

__attribute__((used)) static void can_init_stats(struct net *net)
{
	struct can_pkg_stats *pkg_stats = net->can.pkg_stats;
	struct can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	/*
	 * This memset function is called from a timer context (when
	 * can_stattimer is active which is the default) OR in a process
	 * context (reading the proc_fs when can_stattimer is disabled).
	 */
	memset(pkg_stats, 0, sizeof(struct can_pkg_stats));
	pkg_stats->jiffies_init = jiffies;

	rcv_lists_stats->stats_reset++;

	if (user_reset) {
		user_reset = 0;
		rcv_lists_stats->user_reset++;
	}
}
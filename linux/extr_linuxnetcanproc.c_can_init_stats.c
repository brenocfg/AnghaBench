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
struct s_stats {int /*<<< orphan*/  jiffies_init; } ;
struct s_pstats {int /*<<< orphan*/  user_reset; int /*<<< orphan*/  stats_reset; } ;
struct TYPE_2__ {struct s_pstats* can_pstats; struct s_stats* can_stats; } ;
struct net {TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct s_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ user_reset ; 

__attribute__((used)) static void can_init_stats(struct net *net)
{
	struct s_stats *can_stats = net->can.can_stats;
	struct s_pstats *can_pstats = net->can.can_pstats;
	/*
	 * This memset function is called from a timer context (when
	 * can_stattimer is active which is the default) OR in a process
	 * context (reading the proc_fs when can_stattimer is disabled).
	 */
	memset(can_stats, 0, sizeof(struct s_stats));
	can_stats->jiffies_init = jiffies;

	can_pstats->stats_reset++;

	if (user_reset) {
		user_reset = 0;
		can_pstats->user_reset++;
	}
}
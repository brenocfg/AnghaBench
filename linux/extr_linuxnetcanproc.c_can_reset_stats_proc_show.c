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
struct seq_file {struct net* private; } ;
struct s_stats {scalar_t__ jiffies_init; } ;
struct s_pstats {scalar_t__ stats_reset; } ;
struct TYPE_3__ {scalar_t__ function; } ;
struct TYPE_4__ {TYPE_1__ can_stattimer; struct s_stats* can_stats; struct s_pstats* can_pstats; } ;
struct net {TYPE_2__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_init_stats (struct net*) ; 
 scalar_t__ can_stat_update ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int user_reset ; 

__attribute__((used)) static int can_reset_stats_proc_show(struct seq_file *m, void *v)
{
	struct net *net = m->private;
	struct s_pstats *can_pstats = net->can.can_pstats;
	struct s_stats *can_stats = net->can.can_stats;

	user_reset = 1;

	if (net->can.can_stattimer.function == can_stat_update) {
		seq_printf(m, "Scheduled statistic reset #%ld.\n",
				can_pstats->stats_reset + 1);
	} else {
		if (can_stats->jiffies_init != jiffies)
			can_init_stats(net);

		seq_printf(m, "Performed statistic reset #%ld.\n",
				can_pstats->stats_reset);
	}
	return 0;
}
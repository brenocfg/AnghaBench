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
struct TYPE_3__ {scalar_t__ function; } ;
struct TYPE_4__ {TYPE_1__ stattimer; struct can_rcv_lists_stats* rcv_lists_stats; struct can_pkg_stats* pkg_stats; } ;
struct net {TYPE_2__ can; } ;
struct can_rcv_lists_stats {scalar_t__ user_reset; scalar_t__ stats_reset; scalar_t__ rcv_entries_max; scalar_t__ rcv_entries; } ;
struct can_pkg_stats {scalar_t__ max_rx_rate; scalar_t__ max_tx_rate; scalar_t__ max_rx_match_ratio; scalar_t__ current_rx_rate; scalar_t__ current_tx_rate; scalar_t__ current_rx_match_ratio; scalar_t__ total_rx_rate; scalar_t__ total_tx_rate; scalar_t__ total_rx_match_ratio; scalar_t__ matches; scalar_t__ rx_frames; scalar_t__ tx_frames; } ;

/* Variables and functions */
 scalar_t__ can_stat_update ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int can_stats_proc_show(struct seq_file *m, void *v)
{
	struct net *net = m->private;
	struct can_pkg_stats *pkg_stats = net->can.pkg_stats;
	struct can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;

	seq_putc(m, '\n');
	seq_printf(m, " %8ld transmitted frames (TXF)\n", pkg_stats->tx_frames);
	seq_printf(m, " %8ld received frames (RXF)\n", pkg_stats->rx_frames);
	seq_printf(m, " %8ld matched frames (RXMF)\n", pkg_stats->matches);

	seq_putc(m, '\n');

	if (net->can.stattimer.function == can_stat_update) {
		seq_printf(m, " %8ld %% total match ratio (RXMR)\n",
				pkg_stats->total_rx_match_ratio);

		seq_printf(m, " %8ld frames/s total tx rate (TXR)\n",
				pkg_stats->total_tx_rate);
		seq_printf(m, " %8ld frames/s total rx rate (RXR)\n",
				pkg_stats->total_rx_rate);

		seq_putc(m, '\n');

		seq_printf(m, " %8ld %% current match ratio (CRXMR)\n",
				pkg_stats->current_rx_match_ratio);

		seq_printf(m, " %8ld frames/s current tx rate (CTXR)\n",
				pkg_stats->current_tx_rate);
		seq_printf(m, " %8ld frames/s current rx rate (CRXR)\n",
				pkg_stats->current_rx_rate);

		seq_putc(m, '\n');

		seq_printf(m, " %8ld %% max match ratio (MRXMR)\n",
				pkg_stats->max_rx_match_ratio);

		seq_printf(m, " %8ld frames/s max tx rate (MTXR)\n",
				pkg_stats->max_tx_rate);
		seq_printf(m, " %8ld frames/s max rx rate (MRXR)\n",
				pkg_stats->max_rx_rate);

		seq_putc(m, '\n');
	}

	seq_printf(m, " %8ld current receive list entries (CRCV)\n",
			rcv_lists_stats->rcv_entries);
	seq_printf(m, " %8ld maximum receive list entries (MRCV)\n",
			rcv_lists_stats->rcv_entries_max);

	if (rcv_lists_stats->stats_reset)
		seq_printf(m, "\n %8ld statistic resets (STR)\n",
				rcv_lists_stats->stats_reset);

	if (rcv_lists_stats->user_reset)
		seq_printf(m, " %8ld user statistic resets (USTR)\n",
				rcv_lists_stats->user_reset);

	seq_putc(m, '\n');
	return 0;
}
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
struct seq_file {struct mt7601u_dev* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * aggr_n; int /*<<< orphan*/ * zero_len_del; int /*<<< orphan*/ * aggr_stat; int /*<<< orphan*/ * tx_stat; int /*<<< orphan*/ * rx_stat; } ;
struct mt7601u_dev {int /*<<< orphan*/  avg_ampdu_len; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
mt7601u_ampdu_stat_read(struct seq_file *file, void *data)
{
	struct mt7601u_dev *dev = file->private;
	int i, j;

#define stat_printf(grp, off, name)					\
	seq_printf(file, #name ":\t%llu\n", dev->stats.grp[off])

	stat_printf(rx_stat, 0, rx_crc_err);
	stat_printf(rx_stat, 1, rx_phy_err);
	stat_printf(rx_stat, 2, rx_false_cca);
	stat_printf(rx_stat, 3, rx_plcp_err);
	stat_printf(rx_stat, 4, rx_fifo_overflow);
	stat_printf(rx_stat, 5, rx_duplicate);

	stat_printf(tx_stat, 0, tx_fail_cnt);
	stat_printf(tx_stat, 1, tx_bcn_cnt);
	stat_printf(tx_stat, 2, tx_success);
	stat_printf(tx_stat, 3, tx_retransmit);
	stat_printf(tx_stat, 4, tx_zero_len);
	stat_printf(tx_stat, 5, tx_underflow);

	stat_printf(aggr_stat, 0, non_aggr_tx);
	stat_printf(aggr_stat, 1, aggr_tx);

	stat_printf(zero_len_del, 0, tx_zero_len_del);
	stat_printf(zero_len_del, 1, rx_zero_len_del);
#undef stat_printf

	seq_puts(file, "Aggregations stats:\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 8; j++)
			seq_printf(file, "%08llx ",
				   dev->stats.aggr_n[i * 8 + j]);
		seq_putc(file, '\n');
	}

	seq_printf(file, "recent average AMPDU len: %d\n",
		   atomic_read(&dev->avg_ampdu_len));

	return 0;
}
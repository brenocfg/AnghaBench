#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct minstrel_sta_info {unsigned int n_rates; unsigned int* max_tp_rate; unsigned int max_prob_rate; scalar_t__ sample_packets; scalar_t__ total_packets; struct minstrel_rate* r; } ;
struct minstrel_rate_stats {int prob_ewma; int retry_count; int last_success; int last_attempts; scalar_t__ att_hist; scalar_t__ succ_hist; } ;
struct minstrel_rate {int bitrate; int perfect_tx_time; struct minstrel_rate_stats stats; } ;
struct minstrel_debugfs_info {char* buf; int len; } ;
struct inode {struct minstrel_sta_info* i_private; } ;
struct file {struct minstrel_debugfs_info* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MINSTREL_FRAC (int,int) ; 
 unsigned int MINSTREL_TRUNC (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct minstrel_debugfs_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int minstrel_get_tp_avg (struct minstrel_rate*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int
minstrel_stats_csv_open(struct inode *inode, struct file *file)
{
	struct minstrel_sta_info *mi = inode->i_private;
	struct minstrel_debugfs_info *ms;
	unsigned int i, tp_max, tp_avg, eprob;
	char *p;

	ms = kmalloc(2048, GFP_KERNEL);
	if (!ms)
		return -ENOMEM;

	file->private_data = ms;
	p = ms->buf;

	for (i = 0; i < mi->n_rates; i++) {
		struct minstrel_rate *mr = &mi->r[i];
		struct minstrel_rate_stats *mrs = &mi->r[i].stats;

		p += sprintf(p, "%s" ,((i == mi->max_tp_rate[0]) ? "A" : ""));
		p += sprintf(p, "%s" ,((i == mi->max_tp_rate[1]) ? "B" : ""));
		p += sprintf(p, "%s" ,((i == mi->max_tp_rate[2]) ? "C" : ""));
		p += sprintf(p, "%s" ,((i == mi->max_tp_rate[3]) ? "D" : ""));
		p += sprintf(p, "%s" ,((i == mi->max_prob_rate) ? "P" : ""));

		p += sprintf(p, ",%u%s", mr->bitrate / 2,
				(mr->bitrate & 1 ? ".5," : ","));
		p += sprintf(p, "%u,", i);
		p += sprintf(p, "%u,",mr->perfect_tx_time);

		tp_max = minstrel_get_tp_avg(mr, MINSTREL_FRAC(100,100));
		tp_avg = minstrel_get_tp_avg(mr, mrs->prob_ewma);
		eprob = MINSTREL_TRUNC(mrs->prob_ewma * 1000);

		p += sprintf(p, "%u.%u,%u.%u,%u.%u,%u,%u,%u,"
				"%llu,%llu,%d,%d\n",
				tp_max / 10, tp_max % 10,
				tp_avg / 10, tp_avg % 10,
				eprob / 10, eprob % 10,
				mrs->retry_count,
				mrs->last_success,
				mrs->last_attempts,
				(unsigned long long)mrs->succ_hist,
				(unsigned long long)mrs->att_hist,
				mi->total_packets - mi->sample_packets,
				mi->sample_packets);

	}
	ms->len = p - ms->buf;

	WARN_ON(ms->len + sizeof(*ms) > 2048);

	return 0;
}
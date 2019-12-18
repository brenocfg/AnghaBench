#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct jbd2_stats_proc_session* private; } ;
struct jbd2_stats_proc_session {TYPE_3__* stats; TYPE_1__* journal; } ;
struct TYPE_5__ {int rs_wait; int rs_request_delay; int rs_running; int rs_locked; int rs_flushing; int rs_logging; int rs_handle_count; int rs_blocks; int rs_blocks_logged; } ;
struct TYPE_6__ {int ts_tid; int ts_requested; TYPE_2__ run; } ;
struct TYPE_4__ {int /*<<< orphan*/  j_average_commit_time; int /*<<< orphan*/  j_max_transaction_buffers; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int div_u64 (int /*<<< orphan*/ ,int) ; 
 int jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int jbd2_seq_info_show(struct seq_file *seq, void *v)
{
	struct jbd2_stats_proc_session *s = seq->private;

	if (v != SEQ_START_TOKEN)
		return 0;
	seq_printf(seq, "%lu transactions (%lu requested), "
		   "each up to %u blocks\n",
		   s->stats->ts_tid, s->stats->ts_requested,
		   s->journal->j_max_transaction_buffers);
	if (s->stats->ts_tid == 0)
		return 0;
	seq_printf(seq, "average: \n  %ums waiting for transaction\n",
	    jiffies_to_msecs(s->stats->run.rs_wait / s->stats->ts_tid));
	seq_printf(seq, "  %ums request delay\n",
	    (s->stats->ts_requested == 0) ? 0 :
	    jiffies_to_msecs(s->stats->run.rs_request_delay /
			     s->stats->ts_requested));
	seq_printf(seq, "  %ums running transaction\n",
	    jiffies_to_msecs(s->stats->run.rs_running / s->stats->ts_tid));
	seq_printf(seq, "  %ums transaction was being locked\n",
	    jiffies_to_msecs(s->stats->run.rs_locked / s->stats->ts_tid));
	seq_printf(seq, "  %ums flushing data (in ordered mode)\n",
	    jiffies_to_msecs(s->stats->run.rs_flushing / s->stats->ts_tid));
	seq_printf(seq, "  %ums logging transaction\n",
	    jiffies_to_msecs(s->stats->run.rs_logging / s->stats->ts_tid));
	seq_printf(seq, "  %lluus average transaction commit time\n",
		   div_u64(s->journal->j_average_commit_time, 1000));
	seq_printf(seq, "  %lu handles per transaction\n",
	    s->stats->run.rs_handle_count / s->stats->ts_tid);
	seq_printf(seq, "  %lu blocks per transaction\n",
	    s->stats->run.rs_blocks / s->stats->ts_tid);
	seq_printf(seq, "  %lu logged blocks per transaction\n",
	    s->stats->run.rs_blocks_logged / s->stats->ts_tid);
	return 0;
}
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
struct seq_file {int dummy; } ;
struct sdebug_queue {int /*<<< orphan*/  in_use_bm; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG_VERSION ; 
 int TICK_NSEC ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int dif_errors ; 
 char* dix_reads ; 
 int dix_writes ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int find_last_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  num_aborts ; 
 int /*<<< orphan*/  num_bus_resets ; 
 int /*<<< orphan*/  num_dev_resets ; 
 int /*<<< orphan*/  num_host_resets ; 
 int /*<<< orphan*/  num_target_resets ; 
 int /*<<< orphan*/  sdebug_a_tsf ; 
 int /*<<< orphan*/  sdebug_cmnd_count ; 
 int /*<<< orphan*/  sdebug_completions ; 
 int /*<<< orphan*/  sdebug_cylinders_per ; 
 int /*<<< orphan*/  sdebug_dev_size_mb ; 
 int /*<<< orphan*/  sdebug_every_nth ; 
 int /*<<< orphan*/  sdebug_heads ; 
 int /*<<< orphan*/  sdebug_jdelay ; 
 int /*<<< orphan*/  sdebug_max_luns ; 
 int sdebug_max_queue ; 
 int /*<<< orphan*/  sdebug_miss_cpus ; 
 int /*<<< orphan*/  sdebug_ndelay ; 
 int /*<<< orphan*/  sdebug_num_tgts ; 
 int /*<<< orphan*/  sdebug_opts ; 
 struct sdebug_queue* sdebug_q_arr ; 
 int /*<<< orphan*/  sdebug_sector_size ; 
 int /*<<< orphan*/  sdebug_sectors_per ; 
 int /*<<< orphan*/  sdebug_statistics ; 
 int /*<<< orphan*/  sdebug_version_date ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int submit_queues ; 

__attribute__((used)) static int scsi_debug_show_info(struct seq_file *m, struct Scsi_Host *host)
{
	int f, j, l;
	struct sdebug_queue *sqp;

	seq_printf(m, "scsi_debug adapter driver, version %s [%s]\n",
		   SDEBUG_VERSION, sdebug_version_date);
	seq_printf(m, "num_tgts=%d, %ssize=%d MB, opts=0x%x, every_nth=%d\n",
		   sdebug_num_tgts, "shared (ram) ", sdebug_dev_size_mb,
		   sdebug_opts, sdebug_every_nth);
	seq_printf(m, "delay=%d, ndelay=%d, max_luns=%d, sector_size=%d %s\n",
		   sdebug_jdelay, sdebug_ndelay, sdebug_max_luns,
		   sdebug_sector_size, "bytes");
	seq_printf(m, "cylinders=%d, heads=%d, sectors=%d, command aborts=%d\n",
		   sdebug_cylinders_per, sdebug_heads, sdebug_sectors_per,
		   num_aborts);
	seq_printf(m, "RESETs: device=%d, target=%d, bus=%d, host=%d\n",
		   num_dev_resets, num_target_resets, num_bus_resets,
		   num_host_resets);
	seq_printf(m, "dix_reads=%d, dix_writes=%d, dif_errors=%d\n",
		   dix_reads, dix_writes, dif_errors);
	seq_printf(m, "usec_in_jiffy=%lu, statistics=%d\n", TICK_NSEC / 1000,
		   sdebug_statistics);
	seq_printf(m, "cmnd_count=%d, completions=%d, %s=%d, a_tsf=%d\n",
		   atomic_read(&sdebug_cmnd_count),
		   atomic_read(&sdebug_completions),
		   "miss_cpus", atomic_read(&sdebug_miss_cpus),
		   atomic_read(&sdebug_a_tsf));

	seq_printf(m, "submit_queues=%d\n", submit_queues);
	for (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) {
		seq_printf(m, "  queue %d:\n", j);
		f = find_first_bit(sqp->in_use_bm, sdebug_max_queue);
		if (f != sdebug_max_queue) {
			l = find_last_bit(sqp->in_use_bm, sdebug_max_queue);
			seq_printf(m, "    in_use_bm BUSY: %s: %d,%d\n",
				   "first,last bits", f, l);
		}
	}
	return 0;
}
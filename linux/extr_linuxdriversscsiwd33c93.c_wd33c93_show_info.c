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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */

int
wd33c93_show_info(struct seq_file *m, struct Scsi_Host *instance)
{
#ifdef PROC_INTERFACE
	struct WD33C93_hostdata *hd;
	struct scsi_cmnd *cmd;
	int x;

	hd = (struct WD33C93_hostdata *) instance->hostdata;

	spin_lock_irq(&hd->lock);
	if (hd->proc & PR_VERSION)
		seq_printf(m, "\nVersion %s - %s.",
			WD33C93_VERSION, WD33C93_DATE);

	if (hd->proc & PR_INFO) {
		seq_printf(m, "\nclock_freq=%02x no_sync=%02x no_dma=%d"
			" dma_mode=%02x fast=%d",
			hd->clock_freq, hd->no_sync, hd->no_dma, hd->dma_mode, hd->fast);
		seq_puts(m, "\nsync_xfer[] =       ");
		for (x = 0; x < 7; x++)
			seq_printf(m, "\t%02x", hd->sync_xfer[x]);
		seq_puts(m, "\nsync_stat[] =       ");
		for (x = 0; x < 7; x++)
			seq_printf(m, "\t%02x", hd->sync_stat[x]);
	}
#ifdef PROC_STATISTICS
	if (hd->proc & PR_STATISTICS) {
		seq_puts(m, "\ncommands issued:    ");
		for (x = 0; x < 7; x++)
			seq_printf(m, "\t%ld", hd->cmd_cnt[x]);
		seq_puts(m, "\ndisconnects allowed:");
		for (x = 0; x < 7; x++)
			seq_printf(m, "\t%ld", hd->disc_allowed_cnt[x]);
		seq_puts(m, "\ndisconnects done:   ");
		for (x = 0; x < 7; x++)
			seq_printf(m, "\t%ld", hd->disc_done_cnt[x]);
		seq_printf(m,
			"\ninterrupts: %ld, DATA_PHASE ints: %ld DMA, %ld PIO",
			hd->int_cnt, hd->dma_cnt, hd->pio_cnt);
	}
#endif
	if (hd->proc & PR_CONNECTED) {
		seq_puts(m, "\nconnected:     ");
		if (hd->connected) {
			cmd = (struct scsi_cmnd *) hd->connected;
			seq_printf(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
		}
	}
	if (hd->proc & PR_INPUTQ) {
		seq_puts(m, "\ninput_Q:       ");
		cmd = (struct scsi_cmnd *) hd->input_Q;
		while (cmd) {
			seq_printf(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
			cmd = (struct scsi_cmnd *) cmd->host_scribble;
		}
	}
	if (hd->proc & PR_DISCQ) {
		seq_puts(m, "\ndisconnected_Q:");
		cmd = (struct scsi_cmnd *) hd->disconnected_Q;
		while (cmd) {
			seq_printf(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
			cmd = (struct scsi_cmnd *) cmd->host_scribble;
		}
	}
	seq_putc(m, '\n');
	spin_unlock_irq(&hd->lock);
#endif				/* PROC_INTERFACE */
	return 0;
}
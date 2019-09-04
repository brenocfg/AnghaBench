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
struct seq_file {struct qedi_ctx* private; } ;
struct qedi_io_log {int /*<<< orphan*/  blk_rsp_cpu; int /*<<< orphan*/  intr_cpu; int /*<<< orphan*/  req_cpu; int /*<<< orphan*/  blk_req_cpu; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  result; int /*<<< orphan*/  sg_count; int /*<<< orphan*/  bufflen; int /*<<< orphan*/ * lba; int /*<<< orphan*/  op; int /*<<< orphan*/  lun; int /*<<< orphan*/  cid; int /*<<< orphan*/  task_id; int /*<<< orphan*/  direction; } ;
struct qedi_ctx {int io_trace_idx; int /*<<< orphan*/  io_trace_lock; struct qedi_io_log* io_trace_buf; } ;

/* Variables and functions */
 int QEDI_IO_TRACE_SIZE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
qedi_io_trace_show(struct seq_file *s, void *unused)
{
	int id, idx = 0;
	struct qedi_ctx *qedi = s->private;
	struct qedi_io_log *io_log;
	unsigned long flags;

	seq_puts(s, " DUMP IO LOGS:\n");
	spin_lock_irqsave(&qedi->io_trace_lock, flags);
	idx = qedi->io_trace_idx;
	for (id = 0; id < QEDI_IO_TRACE_SIZE; id++) {
		io_log = &qedi->io_trace_buf[idx];
		seq_printf(s, "iodir-%d:", io_log->direction);
		seq_printf(s, "tid-0x%x:", io_log->task_id);
		seq_printf(s, "cid-0x%x:", io_log->cid);
		seq_printf(s, "lun-%d:", io_log->lun);
		seq_printf(s, "op-0x%02x:", io_log->op);
		seq_printf(s, "0x%02x%02x%02x%02x:", io_log->lba[0],
			   io_log->lba[1], io_log->lba[2], io_log->lba[3]);
		seq_printf(s, "buflen-%d:", io_log->bufflen);
		seq_printf(s, "sgcnt-%d:", io_log->sg_count);
		seq_printf(s, "res-0x%08x:", io_log->result);
		seq_printf(s, "jif-%lu:", io_log->jiffies);
		seq_printf(s, "blk_req_cpu-%d:", io_log->blk_req_cpu);
		seq_printf(s, "req_cpu-%d:", io_log->req_cpu);
		seq_printf(s, "intr_cpu-%d:", io_log->intr_cpu);
		seq_printf(s, "blk_rsp_cpu-%d\n", io_log->blk_rsp_cpu);

		idx++;
		if (idx == QEDI_IO_TRACE_SIZE)
			idx = 0;
	}
	spin_unlock_irqrestore(&qedi->io_trace_lock, flags);
	return 0;
}
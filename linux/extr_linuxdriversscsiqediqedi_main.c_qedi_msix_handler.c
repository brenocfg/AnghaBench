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
struct qedi_fastpath {int /*<<< orphan*/  sb_info; struct qedi_ctx* qedi; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDI_LOG_DISC ; 
 int /*<<< orphan*/  qed_sb_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_sb_update_sb_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ qedi_fp_has_work (struct qedi_fastpath*) ; 
 int qedi_process_completions (struct qedi_fastpath*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static irqreturn_t qedi_msix_handler(int irq, void *dev_id)
{
	struct qedi_fastpath *fp = dev_id;
	struct qedi_ctx *qedi = fp->qedi;
	bool wake_io_thread = true;

	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0);

process_again:
	wake_io_thread = qedi_process_completions(fp);
	if (wake_io_thread) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
			  "process already running\n");
	}

	if (qedi_fp_has_work(fp) == 0)
		qed_sb_update_sb_idx(fp->sb_info);

	/* Check for more work */
	rmb();

	if (qedi_fp_has_work(fp) == 0)
		qed_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
	else
		goto process_again;

	return IRQ_HANDLED;
}
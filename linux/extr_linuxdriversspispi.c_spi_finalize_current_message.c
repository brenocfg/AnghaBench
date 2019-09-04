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
struct spi_message {int /*<<< orphan*/  context; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * state; } ;
struct spi_controller {int cur_msg_prepared; int (* unprepare_message ) (struct spi_controller*,struct spi_message*) ;int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  pump_messages; int /*<<< orphan*/  kworker; struct spi_message* cur_msg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_unmap_msg (struct spi_controller*,struct spi_message*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct spi_controller*,struct spi_message*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_spi_message_done (struct spi_message*) ; 

void spi_finalize_current_message(struct spi_controller *ctlr)
{
	struct spi_message *mesg;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	mesg = ctlr->cur_msg;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	spi_unmap_msg(ctlr, mesg);

	if (ctlr->cur_msg_prepared && ctlr->unprepare_message) {
		ret = ctlr->unprepare_message(ctlr, mesg);
		if (ret) {
			dev_err(&ctlr->dev, "failed to unprepare message: %d\n",
				ret);
		}
	}

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	ctlr->cur_msg = NULL;
	ctlr->cur_msg_prepared = false;
	kthread_queue_work(&ctlr->kworker, &ctlr->pump_messages);
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	trace_spi_message_done(mesg);

	mesg->state = NULL;
	if (mesg->complete)
		mesg->complete(mesg->context);
}
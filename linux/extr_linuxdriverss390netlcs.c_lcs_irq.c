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
struct lcs_channel {scalar_t__ state; int io_idx; int /*<<< orphan*/  irq_tasklet; struct ccw_device* ccwdev; scalar_t__ iob; struct ccw1* ccws; } ;
struct lcs_card {int /*<<< orphan*/  wait_q; struct lcs_channel write; struct lcs_channel read; } ;
struct TYPE_3__ {int cstat; int dstat; int fctl; int actl; scalar_t__ cpa; scalar_t__ cc; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 struct lcs_card* CARD_FROM_DEV (struct ccw_device*) ; 
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_DEV_END ; 
 int DEV_STAT_UNIT_CHECK ; 
 int DEV_STAT_UNIT_EXCEP ; 
 scalar_t__ LCS_CH_STATE_CLEARED ; 
 scalar_t__ LCS_CH_STATE_ERROR ; 
 scalar_t__ LCS_CH_STATE_HALTED ; 
 scalar_t__ LCS_CH_STATE_INIT ; 
 scalar_t__ LCS_CH_STATE_STOPPED ; 
 scalar_t__ LCS_CH_STATE_SUSPENDED ; 
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int,...) ; 
 int LCS_NUM_BUFFS ; 
 int SCHN_STAT_PCI ; 
 int SCSW_ACTL_SUSPENDED ; 
 int SCSW_FCTL_CLEAR_FUNC ; 
 int SCSW_FCTL_HALT_FUNC ; 
 int SCSW_FCTL_START_FUNC ; 
 int /*<<< orphan*/  __lcs_processed_buffer (struct lcs_channel*,scalar_t__) ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_halt (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ lcs_check_irb_error (struct ccw_device*,struct irb*) ; 
 int lcs_get_problem (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  lcs_schedule_recovery (struct lcs_card*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lcs_irq(struct ccw_device *cdev, unsigned long intparm, struct irb *irb)
{
	struct lcs_card *card;
	struct lcs_channel *channel;
	int rc, index;
	int cstat, dstat;

	if (lcs_check_irb_error(cdev, irb))
		return;

	card = CARD_FROM_DEV(cdev);
	if (card->read.ccwdev == cdev)
		channel = &card->read;
	else
		channel = &card->write;

	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;
	LCS_DBF_TEXT_(5, trace, "Rint%s", dev_name(&cdev->dev));
	LCS_DBF_TEXT_(5, trace, "%4x%4x", irb->scsw.cmd.cstat,
		      irb->scsw.cmd.dstat);
	LCS_DBF_TEXT_(5, trace, "%4x%4x", irb->scsw.cmd.fctl,
		      irb->scsw.cmd.actl);

	/* Check for channel and device errors presented */
	rc = lcs_get_problem(cdev, irb);
	if (rc || (dstat & DEV_STAT_UNIT_EXCEP)) {
		dev_warn(&cdev->dev,
			"The LCS device stopped because of an error,"
			" dstat=0x%X, cstat=0x%X \n",
			    dstat, cstat);
		if (rc) {
			channel->state = LCS_CH_STATE_ERROR;
		}
	}
	if (channel->state == LCS_CH_STATE_ERROR) {
		lcs_schedule_recovery(card);
		wake_up(&card->wait_q);
		return;
	}
	/* How far in the ccw chain have we processed? */
	if ((channel->state != LCS_CH_STATE_INIT) &&
	    (irb->scsw.cmd.fctl & SCSW_FCTL_START_FUNC) &&
	    (irb->scsw.cmd.cpa != 0)) {
		index = (struct ccw1 *) __va((addr_t) irb->scsw.cmd.cpa)
			- channel->ccws;
		if ((irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED) ||
		    (irb->scsw.cmd.cstat & SCHN_STAT_PCI))
			/* Bloody io subsystem tells us lies about cpa... */
			index = (index - 1) & (LCS_NUM_BUFFS - 1);
		while (channel->io_idx != index) {
			__lcs_processed_buffer(channel,
					       channel->iob + channel->io_idx);
			channel->io_idx =
				(channel->io_idx + 1) & (LCS_NUM_BUFFS - 1);
		}
	}

	if ((irb->scsw.cmd.dstat & DEV_STAT_DEV_END) ||
	    (irb->scsw.cmd.dstat & DEV_STAT_CHN_END) ||
	    (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK))
		/* Mark channel as stopped. */
		channel->state = LCS_CH_STATE_STOPPED;
	else if (irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED)
		/* CCW execution stopped on a suspend bit. */
		channel->state = LCS_CH_STATE_SUSPENDED;
	if (irb->scsw.cmd.fctl & SCSW_FCTL_HALT_FUNC) {
		if (irb->scsw.cmd.cc != 0) {
			ccw_device_halt(channel->ccwdev, (addr_t) channel);
			return;
		}
		/* The channel has been stopped by halt_IO. */
		channel->state = LCS_CH_STATE_HALTED;
	}
	if (irb->scsw.cmd.fctl & SCSW_FCTL_CLEAR_FUNC)
		channel->state = LCS_CH_STATE_CLEARED;
	/* Do the rest in the tasklet. */
	tasklet_schedule(&channel->irq_tasklet);
}
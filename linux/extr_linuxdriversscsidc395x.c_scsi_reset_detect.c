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
struct TYPE_2__ {int delay_time; } ;
struct AdapterCtlBlk {int acb_flag; int /*<<< orphan*/ * active_dcb; TYPE_1__ eeprom; scalar_t__ last_reset; int /*<<< orphan*/  waiting_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DID_RESET ; 
 int /*<<< orphan*/  DMARESETMODULE ; 
 int /*<<< orphan*/  DO_RSTMODULE ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doing_srb_done (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,struct AdapterCtlBlk*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  reset_dev_param (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  set_basic_config (struct AdapterCtlBlk*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 

__attribute__((used)) static void scsi_reset_detect(struct AdapterCtlBlk *acb)
{
	dprintkl(KERN_INFO, "scsi_reset_detect: acb=%p\n", acb);
	/* delay half a second */
	if (timer_pending(&acb->waiting_timer))
		del_timer(&acb->waiting_timer);

	DC395x_write8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);
	DC395x_write8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);
	/*DC395x_write8(acb, TRM_S1040_DMA_CONTROL,STOPDMAXFER); */
	udelay(500);
	/* Maybe we locked up the bus? Then lets wait even longer ... */
	acb->last_reset =
	    jiffies + 5 * HZ / 2 +
	    HZ * acb->eeprom.delay_time;

	clear_fifo(acb, "scsi_reset_detect");
	set_basic_config(acb);
	/*1.25 */
	/*DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT); */

	if (acb->acb_flag & RESET_DEV) {	/* RESET_DETECT, RESET_DONE, RESET_DEV */
		acb->acb_flag |= RESET_DONE;
	} else {
		acb->acb_flag |= RESET_DETECT;
		reset_dev_param(acb);
		doing_srb_done(acb, DID_RESET, NULL, 1);
		/*DC395x_RecoverSRB( acb ); */
		acb->active_dcb = NULL;
		acb->acb_flag = 0;
		waiting_process_next(acb);
	}
}
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
typedef  size_t u8 ;
struct target_control {int drv_flags; int /*<<< orphan*/  js_period; int /*<<< orphan*/  sconfig0; } ;
struct scsi_ctrl_blk {int status; size_t target; size_t lun; } ;
struct initio_host {scalar_t__ phase; struct scsi_ctrl_blk* active; struct scsi_ctrl_blk* scb; scalar_t__ addr; struct target_control* active_tc; struct target_control* targets; } ;

/* Variables and functions */
 scalar_t__ MSG_IN ; 
 size_t MSG_OTAG ; 
 size_t MSG_STAG ; 
 int SCB_BUSY ; 
 int SCB_SELECT ; 
 int TCF_DRV_EN_TAG ; 
 int /*<<< orphan*/  TSC_XF_FIFO_IN ; 
 scalar_t__ TUL_SBusId ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SCnt0 ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SIdent ; 
 scalar_t__ TUL_SPeriod ; 
 int inb (scalar_t__) ; 
 struct scsi_ctrl_blk* initio_find_busy_scb (struct initio_host*,size_t) ; 
 int initio_msgin_accept (struct initio_host*) ; 
 int initio_msgout_abort_tag (struct initio_host*) ; 
 int initio_msgout_abort_targ (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int wait_tulip (struct initio_host*) ; 

int int_initio_resel(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;
	struct target_control *active_tc;
	u8 tag, msg = 0;
	u8 tar, lun;

	if ((scb = host->active) != NULL) {
		/* FIXME: Why check and not just clear ? */
		if (scb->status & SCB_SELECT)		/* if waiting for selection complete */
			scb->status &= ~SCB_SELECT;
		host->active = NULL;
	}
	/* --------- get target id---------------------- */
	tar = inb(host->addr + TUL_SBusId);
	/* ------ get LUN from Identify message----------- */
	lun = inb(host->addr + TUL_SIdent) & 0x0F;
	/* 07/22/98 from 0x1F -> 0x0F */
	active_tc = &host->targets[tar];
	host->active_tc = active_tc;
	outb(active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(active_tc->js_period, host->addr + TUL_SPeriod);

	/* ------------- tag queueing ? ------------------- */
	if (active_tc->drv_flags & TCF_DRV_EN_TAG) {
		if ((initio_msgin_accept(host)) == -1)
			return -1;
		if (host->phase != MSG_IN)
			goto no_tag;
		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		if (wait_tulip(host) == -1)
			return -1;
		msg = inb(host->addr + TUL_SFifo);	/* Read Tag Message    */

		if (msg < MSG_STAG || msg > MSG_OTAG)		/* Is simple Tag      */
			goto no_tag;

		if (initio_msgin_accept(host) == -1)
			return -1;

		if (host->phase != MSG_IN)
			goto no_tag;

		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		if (wait_tulip(host) == -1)
			return -1;
		tag = inb(host->addr + TUL_SFifo);	/* Read Tag ID       */
		scb = host->scb + tag;
		if (scb->target != tar || scb->lun != lun) {
			return initio_msgout_abort_tag(host);
		}
		if (scb->status != SCB_BUSY) {	/* 03/24/95             */
			return initio_msgout_abort_tag(host);
		}
		host->active = scb;
		if ((initio_msgin_accept(host)) == -1)
			return -1;
	} else {		/* No tag               */
	      no_tag:
		if ((scb = initio_find_busy_scb(host, tar | (lun << 8))) == NULL) {
			return initio_msgout_abort_targ(host);
		}
		host->active = scb;
		if (!(active_tc->drv_flags & TCF_DRV_EN_TAG)) {
			if ((initio_msgin_accept(host)) == -1)
				return -1;
		}
	}
	return 0;
}
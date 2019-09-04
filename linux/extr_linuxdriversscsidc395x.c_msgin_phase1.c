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
typedef  int /*<<< orphan*/  u16 ;
struct ScsiReqBlk {int state; int /*<<< orphan*/  cmd; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write32 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  SCMD_FIFO_IN ; 
 int SRB_DISCONNECT ; 
 int SRB_MSGIN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COUNTER ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msgin_phase1(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	dprintkdbg(DBG_0, "msgin_phase1: (0x%p)\n", srb->cmd);
	clear_fifo(acb, "msgin_phase1");
	DC395x_write32(acb, TRM_S1040_SCSI_COUNTER, 1);
	if (!(srb->state & SRB_MSGIN)) {
		srb->state &= ~SRB_DISCONNECT;
		srb->state |= SRB_MSGIN;
	}
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important for atn stop */
	/* SCSI command */
	DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_IN);
}
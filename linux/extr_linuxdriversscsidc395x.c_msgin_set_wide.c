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
typedef  scalar_t__ u8 ;
struct ScsiReqBlk {scalar_t__* msgin_buf; int state; int msg_count; int /*<<< orphan*/  msgout_buf; struct DeviceCtlBlk* dcb; } ;
struct DeviceCtlBlk {int dev_mode; int sync_mode; int /*<<< orphan*/  target_id; int /*<<< orphan*/  sync_period; } ;
struct AdapterCtlBlk {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_1 ; 
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int HCC_WIDE_CARD ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int NTC_DO_WIDE_NEGO ; 
 int SRB_DO_WIDE_NEGO ; 
 int SYNC_NEGO_DONE ; 
 int SYNC_NEGO_ENABLE ; 
 int WIDE_NEGO_DONE ; 
 int WIDE_NEGO_ENABLE ; 
 int /*<<< orphan*/  WIDE_SYNC ; 
 int /*<<< orphan*/  build_sdtr (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  reprogram_regs (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 

__attribute__((used)) static void msgin_set_wide(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb)
{
	struct DeviceCtlBlk *dcb = srb->dcb;
	u8 wide = (dcb->dev_mode & NTC_DO_WIDE_NEGO
		   && acb->config & HCC_WIDE_CARD) ? 1 : 0;
	dprintkdbg(DBG_1, "msgin_set_wide: <%02i>\n", dcb->target_id);

	if (srb->msgin_buf[3] > wide)
		srb->msgin_buf[3] = wide;
	/* Completed */
	if (!(srb->state & SRB_DO_WIDE_NEGO)) {
		dprintkl(KERN_DEBUG,
			"msgin_set_wide: Wide nego initiated <%02i>\n",
			dcb->target_id);
		memcpy(srb->msgout_buf, srb->msgin_buf, 4);
		srb->msg_count = 4;
		srb->state |= SRB_DO_WIDE_NEGO;
		DC395x_ENABLE_MSGOUT;
	}

	dcb->sync_mode |= (WIDE_NEGO_ENABLE | WIDE_NEGO_DONE);
	if (srb->msgin_buf[3] > 0)
		dcb->sync_period |= WIDE_SYNC;
	else
		dcb->sync_period &= ~WIDE_SYNC;
	srb->state &= ~SRB_DO_WIDE_NEGO;
	/*dcb->sync_mode &= ~(WIDE_NEGO_ENABLE+WIDE_NEGO_DONE); */
	dprintkdbg(DBG_1,
		"msgin_set_wide: Wide (%i bit) negotiated <%02i>\n",
		(8 << srb->msgin_buf[3]), dcb->target_id);
	reprogram_regs(acb, dcb);
	if ((dcb->sync_mode & SYNC_NEGO_ENABLE)
	    && !(dcb->sync_mode & SYNC_NEGO_DONE)) {
		build_sdtr(acb, dcb, srb);
		DC395x_ENABLE_MSGOUT;
		dprintkdbg(DBG_0, "msgin_set_wide: Also try SDTR.\n");
	}
}
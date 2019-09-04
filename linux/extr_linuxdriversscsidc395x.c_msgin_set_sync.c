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
typedef  int u8 ;
struct ScsiReqBlk {int* msgin_buf; int state; int msg_count; int /*<<< orphan*/  msgout_buf; struct DeviceCtlBlk* dcb; } ;
struct DeviceCtlBlk {int dev_mode; int sync_offset; int min_nego_period; int sync_period; int sync_mode; int /*<<< orphan*/  target_id; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int ALT_SYNC ; 
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_1 ; 
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int NTC_DO_SYNC_NEGO ; 
 int SRB_DO_SYNC_NEGO ; 
 int SYNC_NEGO_DONE ; 
 int SYNC_NEGO_ENABLE ; 
 int WIDE_NEGO_DONE ; 
 int WIDE_NEGO_ENABLE ; 
 int WIDE_SYNC ; 
 int /*<<< orphan*/  build_wdtr (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int* clock_period ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  reprogram_regs (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 

__attribute__((used)) static void msgin_set_sync(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb)
{
	struct DeviceCtlBlk *dcb = srb->dcb;
	u8 bval;
	int fact;
	dprintkdbg(DBG_1, "msgin_set_sync: <%02i> Sync: %ins "
		"(%02i.%01i MHz) Offset %i\n",
		dcb->target_id, srb->msgin_buf[3] << 2,
		(250 / srb->msgin_buf[3]),
		((250 % srb->msgin_buf[3]) * 10) / srb->msgin_buf[3],
		srb->msgin_buf[4]);

	if (srb->msgin_buf[4] > 15)
		srb->msgin_buf[4] = 15;
	if (!(dcb->dev_mode & NTC_DO_SYNC_NEGO))
		dcb->sync_offset = 0;
	else if (dcb->sync_offset == 0)
		dcb->sync_offset = srb->msgin_buf[4];
	if (srb->msgin_buf[4] > dcb->sync_offset)
		srb->msgin_buf[4] = dcb->sync_offset;
	else
		dcb->sync_offset = srb->msgin_buf[4];
	bval = 0;
	while (bval < 7 && (srb->msgin_buf[3] > clock_period[bval]
			    || dcb->min_nego_period >
			    clock_period[bval]))
		bval++;
	if (srb->msgin_buf[3] < clock_period[bval])
		dprintkl(KERN_INFO,
			"msgin_set_sync: Increase sync nego period to %ins\n",
			clock_period[bval] << 2);
	srb->msgin_buf[3] = clock_period[bval];
	dcb->sync_period &= 0xf0;
	dcb->sync_period |= ALT_SYNC | bval;
	dcb->min_nego_period = srb->msgin_buf[3];

	if (dcb->sync_period & WIDE_SYNC)
		fact = 500;
	else
		fact = 250;

	dprintkl(KERN_INFO,
		"Target %02i: %s Sync: %ins Offset %i (%02i.%01i MB/s)\n",
		dcb->target_id, (fact == 500) ? "Wide16" : "",
		dcb->min_nego_period << 2, dcb->sync_offset,
		(fact / dcb->min_nego_period),
		((fact % dcb->min_nego_period) * 10 +
		dcb->min_nego_period / 2) / dcb->min_nego_period);

	if (!(srb->state & SRB_DO_SYNC_NEGO)) {
		/* Reply with corrected SDTR Message */
		dprintkl(KERN_DEBUG, "msgin_set_sync: answer w/%ins %i\n",
			srb->msgin_buf[3] << 2, srb->msgin_buf[4]);

		memcpy(srb->msgout_buf, srb->msgin_buf, 5);
		srb->msg_count = 5;
		DC395x_ENABLE_MSGOUT;
		dcb->sync_mode |= SYNC_NEGO_DONE;
	} else {
		if ((dcb->sync_mode & WIDE_NEGO_ENABLE)
		    && !(dcb->sync_mode & WIDE_NEGO_DONE)) {
			build_wdtr(acb, dcb, srb);
			DC395x_ENABLE_MSGOUT;
			dprintkdbg(DBG_0, "msgin_set_sync: Also try WDTR\n");
		}
	}
	srb->state &= ~SRB_DO_SYNC_NEGO;
	dcb->sync_mode |= SYNC_NEGO_DONE | SYNC_NEGO_ENABLE;

	reprogram_regs(acb, dcb);
}
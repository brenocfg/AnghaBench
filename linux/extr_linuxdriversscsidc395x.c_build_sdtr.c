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
typedef  int /*<<< orphan*/  u8 ;
struct ScsiReqBlk {int msg_count; int /*<<< orphan*/  state; int /*<<< orphan*/ * msgout_buf; } ;
struct DeviceCtlBlk {int dev_mode; int min_nego_period; int /*<<< orphan*/  sync_offset; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENDED_SDTR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MSG_EXTENDED ; 
 int NTC_DO_SYNC_NEGO ; 
 int /*<<< orphan*/  SRB_DO_SYNC_NEGO ; 
 int /*<<< orphan*/  SYNC_NEGO_OFFSET ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_sdtr(struct AdapterCtlBlk *acb, struct DeviceCtlBlk *dcb,
		struct ScsiReqBlk *srb)
{
	u8 *ptr = srb->msgout_buf + srb->msg_count;
	if (srb->msg_count > 1) {
		dprintkl(KERN_INFO,
			"build_sdtr: msgout_buf BUSY (%i: %02x %02x)\n",
			srb->msg_count, srb->msgout_buf[0],
			srb->msgout_buf[1]);
		return;
	}
	if (!(dcb->dev_mode & NTC_DO_SYNC_NEGO)) {
		dcb->sync_offset = 0;
		dcb->min_nego_period = 200 >> 2;
	} else if (dcb->sync_offset == 0)
		dcb->sync_offset = SYNC_NEGO_OFFSET;

	*ptr++ = MSG_EXTENDED;	/* (01h) */
	*ptr++ = 3;		/* length */
	*ptr++ = EXTENDED_SDTR;	/* (01h) */
	*ptr++ = dcb->min_nego_period;	/* Transfer period (in 4ns) */
	*ptr++ = dcb->sync_offset;	/* Transfer period (max. REQ/ACK dist) */
	srb->msg_count += 5;
	srb->state |= SRB_DO_SYNC_NEGO;
}
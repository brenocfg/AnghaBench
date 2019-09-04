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
struct ScsiReqBlk {int* msgout_buf; int msg_count; int /*<<< orphan*/  state; } ;
struct DeviceCtlBlk {int dev_mode; } ;
struct AdapterCtlBlk {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENDED_WDTR ; 
 int HCC_WIDE_CARD ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MSG_EXTENDED ; 
 int NTC_DO_WIDE_NEGO ; 
 int /*<<< orphan*/  SRB_DO_WIDE_NEGO ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void build_wdtr(struct AdapterCtlBlk *acb, struct DeviceCtlBlk *dcb,
		struct ScsiReqBlk *srb)
{
	u8 wide = ((dcb->dev_mode & NTC_DO_WIDE_NEGO) &
		   (acb->config & HCC_WIDE_CARD)) ? 1 : 0;
	u8 *ptr = srb->msgout_buf + srb->msg_count;
	if (srb->msg_count > 1) {
		dprintkl(KERN_INFO,
			"build_wdtr: msgout_buf BUSY (%i: %02x %02x)\n",
			srb->msg_count, srb->msgout_buf[0],
			srb->msgout_buf[1]);
		return;
	}
	*ptr++ = MSG_EXTENDED;	/* (01h) */
	*ptr++ = 2;		/* length */
	*ptr++ = EXTENDED_WDTR;	/* (03h) */
	*ptr++ = wide;
	srb->msg_count += 4;
	srb->state |= SRB_DO_WIDE_NEGO;
}
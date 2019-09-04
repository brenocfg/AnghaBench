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
typedef  int u32 ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
#define  AdapNormCmdQue 134 
#define  AdapNormRespQue 133 
#define  AdapPrintfDone 132 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DOORBELL_1 ; 
 int /*<<< orphan*/  DOORBELL_2 ; 
 int /*<<< orphan*/  DOORBELL_3 ; 
 int /*<<< orphan*/  DOORBELL_4 ; 
 int /*<<< orphan*/  DOORBELL_5 ; 
 int /*<<< orphan*/  DOORBELL_6 ; 
 int /*<<< orphan*/  DoorbellReg_s ; 
#define  FastIo 131 
#define  HostNormCmdNotFull 130 
#define  HostNormRespNotFull 129 
#define  HostShutdown 128 
 int /*<<< orphan*/  sa_writew (struct aac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aac_sa_notify_adapter(struct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNormCmdQue:
		sa_writew(dev, DoorbellReg_s,DOORBELL_1);
		break;
	case HostNormRespNotFull:
		sa_writew(dev, DoorbellReg_s,DOORBELL_4);
		break;
	case AdapNormRespQue:
		sa_writew(dev, DoorbellReg_s,DOORBELL_2);
		break;
	case HostNormCmdNotFull:
		sa_writew(dev, DoorbellReg_s,DOORBELL_3);
		break;
	case HostShutdown:
		/*
		sa_sync_cmd(dev, HOST_CRASHING, 0, 0, 0, 0, 0, 0,
		NULL, NULL, NULL, NULL, NULL);
		*/
		break;
	case FastIo:
		sa_writew(dev, DoorbellReg_s,DOORBELL_6);
		break;
	case AdapPrintfDone:
		sa_writew(dev, DoorbellReg_s,DOORBELL_5);
		break;
	default:
		BUG();
		break;
	}
}
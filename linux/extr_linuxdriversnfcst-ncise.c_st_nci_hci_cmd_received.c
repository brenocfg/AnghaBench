#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {int se_active; int /*<<< orphan*/  req_completion; int /*<<< orphan*/  se_active_timer; } ;
struct st_nci_info {TYPE_3__ se_info; } ;
struct sk_buff {int dummy; } ;
struct nci_dev {TYPE_2__* hci_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  count_pipes; int /*<<< orphan*/  expected_pipes; TYPE_1__* pipes; } ;
struct TYPE_4__ {size_t gate; int /*<<< orphan*/  host; } ;

/* Variables and functions */
#define  NCI_HCI_ANY_OPEN_PIPE 128 
 size_t ST_NCI_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST_NCI_UICC_HOST_ID ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 

void st_nci_hci_cmd_received(struct nci_dev *ndev, u8 pipe, u8 cmd,
			       struct sk_buff *skb)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);
	u8 gate = ndev->hci_dev->pipes[pipe].gate;

	pr_debug("cmd: %x\n", cmd);

	switch (cmd) {
	case NCI_HCI_ANY_OPEN_PIPE:
		if (gate != ST_NCI_APDU_READER_GATE &&
		    ndev->hci_dev->pipes[pipe].host != ST_NCI_UICC_HOST_ID)
			ndev->hci_dev->count_pipes++;

		if (ndev->hci_dev->count_pipes ==
		    ndev->hci_dev->expected_pipes) {
			del_timer_sync(&info->se_info.se_active_timer);
			info->se_info.se_active = false;
			ndev->hci_dev->count_pipes = 0;
			complete(&info->se_info.req_completion);
		}
	break;
	}
}
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
typedef  int u8 ;
struct TYPE_4__ {int se_active; int /*<<< orphan*/  se_active_timer; int /*<<< orphan*/  req_completion; } ;
struct st_nci_info {TYPE_2__ se_info; } ;
struct sk_buff {int dummy; } ;
struct nci_dev {TYPE_1__* nfc_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ST_NCI_EVT_HOT_PLUG 128 
 int /*<<< orphan*/  ST_NCI_EVT_HOT_PLUG_IS_INHIBITED (struct sk_buff*) ; 
 int /*<<< orphan*/  ST_NCI_SE_TO_PIPES ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void st_nci_hci_admin_event_received(struct nci_dev *ndev,
					      u8 event, struct sk_buff *skb)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	switch (event) {
	case ST_NCI_EVT_HOT_PLUG:
		if (info->se_info.se_active) {
			if (!ST_NCI_EVT_HOT_PLUG_IS_INHIBITED(skb)) {
				del_timer_sync(&info->se_info.se_active_timer);
				info->se_info.se_active = false;
				complete(&info->se_info.req_completion);
			} else {
				mod_timer(&info->se_info.se_active_timer,
				      jiffies +
				      msecs_to_jiffies(ST_NCI_SE_TO_PIPES));
			}
		}
	break;
	default:
		nfc_err(&ndev->nfc_dev->dev, "Unexpected event on admin gate\n");
	}
}
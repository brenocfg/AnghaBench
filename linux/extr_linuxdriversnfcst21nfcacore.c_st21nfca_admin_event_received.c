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
struct st21nfca_hci_info {TYPE_2__ se_info; } ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {TYPE_1__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ST21NFCA_EVT_HOT_PLUG 128 
 int /*<<< orphan*/  ST21NFCA_EVT_HOT_PLUG_IS_INHIBITED (struct sk_buff*) ; 
 int /*<<< orphan*/  ST21NFCA_SE_TO_PIPES ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int st21nfca_admin_event_received(struct nfc_hci_dev *hdev, u8 event,
					struct sk_buff *skb)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("admin event: %x\n", event);

	switch (event) {
	case ST21NFCA_EVT_HOT_PLUG:
		if (info->se_info.se_active) {
			if (!ST21NFCA_EVT_HOT_PLUG_IS_INHIBITED(skb)) {
				del_timer_sync(&info->se_info.se_active_timer);
				info->se_info.se_active = false;
				complete(&info->se_info.req_completion);
			} else {
				mod_timer(&info->se_info.se_active_timer,
					jiffies +
					msecs_to_jiffies(ST21NFCA_SE_TO_PIPES));
			}
		}
	break;
	default:
		nfc_err(&hdev->ndev->dev, "Unexpected event on admin gate\n");
	}
	kfree_skb(skb);
	return 0;
}
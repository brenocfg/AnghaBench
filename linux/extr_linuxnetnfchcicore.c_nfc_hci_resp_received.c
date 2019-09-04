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
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {int /*<<< orphan*/  msg_tx_mutex; int /*<<< orphan*/ * cmd_pending_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfc_hci_cmd_completion (struct nfc_hci_dev*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_hci_result_to_errno (int /*<<< orphan*/ ) ; 

void nfc_hci_resp_received(struct nfc_hci_dev *hdev, u8 result,
			   struct sk_buff *skb)
{
	mutex_lock(&hdev->msg_tx_mutex);

	if (hdev->cmd_pending_msg == NULL) {
		kfree_skb(skb);
		goto exit;
	}

	__nfc_hci_cmd_completion(hdev, nfc_hci_result_to_errno(result), skb);

exit:
	mutex_unlock(&hdev->msg_tx_mutex);
}
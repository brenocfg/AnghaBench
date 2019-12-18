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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {void* le_def_tx_time; void* le_def_tx_len; int /*<<< orphan*/  name; } ;
struct hci_cp_le_write_def_data_len {int /*<<< orphan*/  tx_time; int /*<<< orphan*/  tx_len; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_LE_WRITE_DEF_DATA_LEN ; 
 struct hci_cp_le_write_def_data_len* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_write_def_data_len(struct hci_dev *hdev,
					 struct sk_buff *skb)
{
	struct hci_cp_le_write_def_data_len *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_WRITE_DEF_DATA_LEN);
	if (!sent)
		return;

	hdev->le_def_tx_len = le16_to_cpu(sent->tx_len);
	hdev->le_def_tx_time = le16_to_cpu(sent->tx_time);
}
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
struct hci_rp_le_read_def_data_len {int /*<<< orphan*/  tx_time; int /*<<< orphan*/  tx_len; scalar_t__ status; } ;
struct hci_dev {void* le_def_tx_time; void* le_def_tx_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_read_def_data_len(struct hci_dev *hdev,
					struct sk_buff *skb)
{
	struct hci_rp_le_read_def_data_len *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	hdev->le_def_tx_len = le16_to_cpu(rp->tx_len);
	hdev->le_def_tx_time = le16_to_cpu(rp->tx_time);
}
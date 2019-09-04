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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_ANY_GET_PARAMETER ; 
 int nfc_hci_send_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_hci_get_param(struct nfc_hci_dev *hdev, u8 gate, u8 idx,
		      struct sk_buff **skb)
{
	pr_debug("gate=%d regidx=%d\n", gate, idx);

	return nfc_hci_send_cmd(hdev, gate, NFC_HCI_ANY_GET_PARAMETER,
				&idx, 1, skb);
}
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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {size_t* gate2pipe; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 size_t NFC_HCI_INVALID_PIPE ; 
 int nfc_hci_execute_cmd (struct nfc_hci_dev*,size_t,size_t,size_t const*,size_t,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int nfc_hci_send_cmd(struct nfc_hci_dev *hdev, u8 gate, u8 cmd,
		     const u8 *param, size_t param_len, struct sk_buff **skb)
{
	u8 pipe;

	pr_debug("\n");

	pipe = hdev->gate2pipe[gate];
	if (pipe == NFC_HCI_INVALID_PIPE)
		return -EADDRNOTAVAIL;

	return nfc_hci_execute_cmd(hdev, pipe, cmd, param, param_len, skb);
}
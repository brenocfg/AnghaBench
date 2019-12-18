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
struct nfc_hci_dev {size_t* gate2pipe; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  NFC_HCI_HCP_EVENT ; 
 size_t NFC_HCI_INVALID_PIPE ; 
 int nfc_hci_hcp_message_tx (struct nfc_hci_dev*,size_t,int /*<<< orphan*/ ,size_t,size_t const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t) ; 

int nfc_hci_send_event(struct nfc_hci_dev *hdev, u8 gate, u8 event,
		       const u8 *param, size_t param_len)
{
	u8 pipe;

	pr_debug("%d to gate %d\n", event, gate);

	pipe = hdev->gate2pipe[gate];
	if (pipe == NFC_HCI_INVALID_PIPE)
		return -EADDRNOTAVAIL;

	return nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_EVENT, event,
				      param, param_len, NULL, NULL, 0);
}
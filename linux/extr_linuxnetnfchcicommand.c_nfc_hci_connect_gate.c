#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct nfc_hci_dev {size_t* gate2pipe; TYPE_1__* pipes; } ;
struct TYPE_2__ {size_t gate; size_t dest_host; } ;

/* Variables and functions */
 int EADDRINUSE ; 
#define  NFC_HCI_ADMIN_GATE 129 
 size_t NFC_HCI_ADMIN_PIPE ; 
 size_t NFC_HCI_DO_NOT_CREATE_PIPE ; 
 size_t NFC_HCI_INVALID_PIPE ; 
#define  NFC_HCI_LINK_MGMT_GATE 128 
 size_t NFC_HCI_LINK_MGMT_PIPE ; 
 size_t nfc_hci_create_pipe (struct nfc_hci_dev*,size_t,size_t,int*) ; 
 scalar_t__ nfc_hci_delete_pipe (struct nfc_hci_dev*,size_t) ; 
 int nfc_hci_open_pipe (struct nfc_hci_dev*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int nfc_hci_connect_gate(struct nfc_hci_dev *hdev, u8 dest_host, u8 dest_gate,
			 u8 pipe)
{
	bool pipe_created = false;
	int r;

	pr_debug("\n");

	if (pipe == NFC_HCI_DO_NOT_CREATE_PIPE)
		return 0;

	if (hdev->gate2pipe[dest_gate] != NFC_HCI_INVALID_PIPE)
		return -EADDRINUSE;

	if (pipe != NFC_HCI_INVALID_PIPE)
		goto open_pipe;

	switch (dest_gate) {
	case NFC_HCI_LINK_MGMT_GATE:
		pipe = NFC_HCI_LINK_MGMT_PIPE;
		break;
	case NFC_HCI_ADMIN_GATE:
		pipe = NFC_HCI_ADMIN_PIPE;
		break;
	default:
		pipe = nfc_hci_create_pipe(hdev, dest_host, dest_gate, &r);
		if (pipe == NFC_HCI_INVALID_PIPE)
			return r;
		pipe_created = true;
		break;
	}

open_pipe:
	r = nfc_hci_open_pipe(hdev, pipe);
	if (r < 0) {
		if (pipe_created)
			if (nfc_hci_delete_pipe(hdev, pipe) < 0) {
				/* TODO: Cannot clean by deleting pipe...
				 * -> inconsistent state */
			}
		return r;
	}

	hdev->pipes[pipe].gate = dest_gate;
	hdev->pipes[pipe].dest_host = dest_host;
	hdev->gate2pipe[dest_gate] = pipe;

	return 0;
}
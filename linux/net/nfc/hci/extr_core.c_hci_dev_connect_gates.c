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
struct nfc_hci_gate {int /*<<< orphan*/  pipe; int /*<<< orphan*/  gate; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_HOST_CONTROLLER_ID ; 
 int nfc_hci_connect_gate (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hci_dev_connect_gates(struct nfc_hci_dev *hdev, u8 gate_count,
				 struct nfc_hci_gate *gates)
{
	int r;
	while (gate_count--) {
		r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
					 gates->gate, gates->pipe);
		if (r < 0)
			return r;
		gates++;
	}

	return 0;
}
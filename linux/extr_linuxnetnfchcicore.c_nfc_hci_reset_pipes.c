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
struct nfc_hci_dev {int /*<<< orphan*/  gate2pipe; TYPE_1__* pipes; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest_host; int /*<<< orphan*/  gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_INVALID_GATE ; 
 int /*<<< orphan*/  NFC_HCI_INVALID_HOST ; 
 int /*<<< orphan*/  NFC_HCI_INVALID_PIPE ; 
 int NFC_HCI_MAX_PIPES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void nfc_hci_reset_pipes(struct nfc_hci_dev *hdev)
{
	int i = 0;

	for (i = 0; i < NFC_HCI_MAX_PIPES; i++) {
		hdev->pipes[i].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[i].dest_host = NFC_HCI_INVALID_HOST;
	}
	memset(hdev->gate2pipe, NFC_HCI_INVALID_PIPE, sizeof(hdev->gate2pipe));
}
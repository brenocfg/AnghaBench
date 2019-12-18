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
typedef  scalar_t__ u8 ;
struct nfc_hci_dev {TYPE_1__* pipes; } ;
struct TYPE_2__ {scalar_t__ dest_host; int /*<<< orphan*/  gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_INVALID_GATE ; 
 scalar_t__ NFC_HCI_INVALID_HOST ; 
 int NFC_HCI_MAX_PIPES ; 

void nfc_hci_reset_pipes_per_host(struct nfc_hci_dev *hdev, u8 host)
{
	int i = 0;

	for (i = 0; i < NFC_HCI_MAX_PIPES; i++) {
		if (hdev->pipes[i].dest_host != host)
			continue;

		hdev->pipes[i].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[i].dest_host = NFC_HCI_INVALID_HOST;
	}
}
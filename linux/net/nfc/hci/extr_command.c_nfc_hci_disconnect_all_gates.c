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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int nfc_hci_clear_all_pipes (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  nfc_hci_reset_pipes (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int nfc_hci_disconnect_all_gates(struct nfc_hci_dev *hdev)
{
	int r;

	pr_debug("\n");

	r = nfc_hci_clear_all_pipes(hdev);
	if (r < 0)
		return r;

	nfc_hci_reset_pipes(hdev);

	return 0;
}
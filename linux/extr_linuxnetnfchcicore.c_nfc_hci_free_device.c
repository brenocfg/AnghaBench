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
struct nfc_hci_dev {int /*<<< orphan*/  llc; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  nfc_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llc_free (int /*<<< orphan*/ ) ; 

void nfc_hci_free_device(struct nfc_hci_dev *hdev)
{
	nfc_free_device(hdev->ndev);
	nfc_llc_free(hdev->llc);
	kfree(hdev);
}
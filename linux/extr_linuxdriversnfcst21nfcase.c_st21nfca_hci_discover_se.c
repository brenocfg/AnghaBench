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
struct st21nfca_hci_info {TYPE_1__* se_status; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  quirks; } ;
struct TYPE_2__ {scalar_t__ is_ese_present; scalar_t__ is_uicc_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_UICC_HOST_ID ; 
 int /*<<< orphan*/  NFC_SE_EMBEDDED ; 
 int /*<<< orphan*/  NFC_SE_UICC ; 
 int /*<<< orphan*/  ST21NFCA_ESE_HOST_ID ; 
 int /*<<< orphan*/  ST21NFCA_FACTORY_MODE ; 
 int /*<<< orphan*/  nfc_add_se (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int st21nfca_hci_discover_se(struct nfc_hci_dev *hdev)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	int se_count = 0;

	if (test_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks))
		return 0;

	if (info->se_status->is_uicc_present) {
		nfc_add_se(hdev->ndev, NFC_HCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	}

	if (info->se_status->is_ese_present) {
		nfc_add_se(hdev->ndev, ST21NFCA_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	}

	return !se_count;
}
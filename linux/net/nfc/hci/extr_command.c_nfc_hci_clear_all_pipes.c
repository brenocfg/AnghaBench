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
struct nfc_hci_dev {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_ADMIN_PIPE ; 
 int /*<<< orphan*/  NFC_HCI_ADM_CLEAR_ALL_PIPE ; 
 int /*<<< orphan*/  NFC_HCI_QUIRK_SHORT_CLEAR ; 
 int nfc_hci_execute_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfc_hci_clear_all_pipes(struct nfc_hci_dev *hdev)
{
	u8 param[2];
	size_t param_len = 2;

	/* TODO: Find out what the identity reference data is
	 * and fill param with it. HCI spec 6.1.3.5 */

	pr_debug("\n");

	if (test_bit(NFC_HCI_QUIRK_SHORT_CLEAR, &hdev->quirks))
		param_len = 0;

	return nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_CLEAR_ALL_PIPE, param, param_len,
				   NULL);
}
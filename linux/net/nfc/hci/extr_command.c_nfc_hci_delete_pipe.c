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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_ADMIN_PIPE ; 
 int /*<<< orphan*/  NFC_HCI_ADM_DELETE_PIPE ; 
 int nfc_hci_execute_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int nfc_hci_delete_pipe(struct nfc_hci_dev *hdev, u8 pipe)
{
	pr_debug("\n");

	return nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_DELETE_PIPE, &pipe, 1, NULL);
}
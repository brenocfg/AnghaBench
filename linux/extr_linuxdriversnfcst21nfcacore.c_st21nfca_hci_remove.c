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
struct st21nfca_hci_info {int dummy; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct st21nfca_hci_info*) ; 
 int /*<<< orphan*/  nfc_hci_free_device (struct nfc_hci_dev*) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  nfc_hci_unregister_device (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  st21nfca_dep_deinit (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  st21nfca_se_deinit (struct nfc_hci_dev*) ; 

void st21nfca_hci_remove(struct nfc_hci_dev *hdev)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	st21nfca_dep_deinit(hdev);
	st21nfca_se_deinit(hdev);
	nfc_hci_unregister_device(hdev);
	nfc_hci_free_device(hdev);
	kfree(info);
}
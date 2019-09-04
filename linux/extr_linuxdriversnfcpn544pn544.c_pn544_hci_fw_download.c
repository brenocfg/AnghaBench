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
struct pn544_hci_info {int (* fw_download ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_id; } ;
struct nfc_hci_dev {int /*<<< orphan*/  sw_romlib; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct pn544_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pn544_hci_fw_download(struct nfc_hci_dev *hdev,
				 const char *firmware_name)
{
	struct pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	if (info->fw_download == NULL)
		return -ENOTSUPP;

	return info->fw_download(info->phy_id, firmware_name, hdev->sw_romlib);
}
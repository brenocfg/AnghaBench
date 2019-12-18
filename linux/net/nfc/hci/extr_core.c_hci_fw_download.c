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
struct nfc_hci_dev {TYPE_1__* ops; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int (* fw_download ) (struct nfc_hci_dev*,char const*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int stub1 (struct nfc_hci_dev*,char const*) ; 

__attribute__((used)) static int hci_fw_download(struct nfc_dev *nfc_dev, const char *firmware_name)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	if (!hdev->ops->fw_download)
		return -ENOTSUPP;

	return hdev->ops->fw_download(hdev, firmware_name);
}
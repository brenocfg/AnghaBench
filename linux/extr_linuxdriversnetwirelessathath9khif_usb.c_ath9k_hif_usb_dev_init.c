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
struct hif_device_usb {TYPE_1__* udev; int /*<<< orphan*/  fw_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ath9k_hif_usb_alloc_urbs (struct hif_device_usb*) ; 
 int ath9k_hif_usb_download_fw (struct hif_device_usb*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int ath9k_hif_usb_dev_init(struct hif_device_usb *hif_dev)
{
	int ret;

	ret = ath9k_hif_usb_download_fw(hif_dev);
	if (ret) {
		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Firmware - %s download failed\n",
			hif_dev->fw_name);
		return ret;
	}

	/* Alloc URBs */
	ret = ath9k_hif_usb_alloc_urbs(hif_dev);
	if (ret) {
		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Unable to allocate URBs\n");
		return ret;
	}

	return 0;
}
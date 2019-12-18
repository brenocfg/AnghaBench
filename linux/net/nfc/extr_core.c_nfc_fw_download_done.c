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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_dev {int fw_download_in_progress; } ;

/* Variables and functions */
 int nfc_genl_fw_download_done (struct nfc_dev*,char const*,int /*<<< orphan*/ ) ; 

int nfc_fw_download_done(struct nfc_dev *dev, const char *firmware_name,
			 u32 result)
{
	dev->fw_download_in_progress = false;

	return nfc_genl_fw_download_done(dev, firmware_name, result);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rt2x00_dev {struct firmware const* fw; TYPE_3__* ops; TYPE_1__* hw; } ;
struct firmware {int size; int* data; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fw_version; } ;
struct TYPE_7__ {TYPE_2__* lib; } ;
struct TYPE_6__ {char* (* get_firmware_name ) (struct rt2x00_dev*) ;int (* check_firmware ) (struct rt2x00_dev*,int*,int) ;} ;
struct TYPE_5__ {TYPE_4__* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_PROJECT ; 
 int EINVAL ; 
 int ENOENT ; 
#define  FW_BAD_CRC 131 
#define  FW_BAD_LENGTH 130 
#define  FW_BAD_VERSION 129 
#define  FW_OK 128 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,...) ; 
 int /*<<< orphan*/  rt2x00_info (struct rt2x00_dev*,char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 char* stub1 (struct rt2x00_dev*) ; 
 int stub2 (struct rt2x00_dev*,int*,int) ; 
 struct device* wiphy_dev (TYPE_4__*) ; 

__attribute__((used)) static int rt2x00lib_request_firmware(struct rt2x00_dev *rt2x00dev)
{
	struct device *device = wiphy_dev(rt2x00dev->hw->wiphy);
	const struct firmware *fw;
	char *fw_name;
	int retval;

	/*
	 * Read correct firmware from harddisk.
	 */
	fw_name = rt2x00dev->ops->lib->get_firmware_name(rt2x00dev);
	if (!fw_name) {
		rt2x00_err(rt2x00dev,
			   "Invalid firmware filename\n"
			   "Please file bug report to %s\n", DRV_PROJECT);
		return -EINVAL;
	}

	rt2x00_info(rt2x00dev, "Loading firmware file '%s'\n", fw_name);

	retval = request_firmware(&fw, fw_name, device);
	if (retval) {
		rt2x00_err(rt2x00dev, "Failed to request Firmware\n");
		return retval;
	}

	if (!fw || !fw->size || !fw->data) {
		rt2x00_err(rt2x00dev, "Failed to read Firmware\n");
		release_firmware(fw);
		return -ENOENT;
	}

	rt2x00_info(rt2x00dev, "Firmware detected - version: %d.%d\n",
		    fw->data[fw->size - 4], fw->data[fw->size - 3]);
	snprintf(rt2x00dev->hw->wiphy->fw_version,
			sizeof(rt2x00dev->hw->wiphy->fw_version), "%d.%d",
			fw->data[fw->size - 4], fw->data[fw->size - 3]);

	retval = rt2x00dev->ops->lib->check_firmware(rt2x00dev, fw->data, fw->size);
	switch (retval) {
	case FW_OK:
		break;
	case FW_BAD_CRC:
		rt2x00_err(rt2x00dev, "Firmware checksum error\n");
		goto exit;
	case FW_BAD_LENGTH:
		rt2x00_err(rt2x00dev, "Invalid firmware file length (len=%zu)\n",
			   fw->size);
		goto exit;
	case FW_BAD_VERSION:
		rt2x00_err(rt2x00dev, "Current firmware does not support detected chipset\n");
		goto exit;
	}

	rt2x00dev->fw = fw;

	return 0;

exit:
	release_firmware(fw);

	return -ENOENT;
}
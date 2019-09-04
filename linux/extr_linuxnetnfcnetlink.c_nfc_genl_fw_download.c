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
struct sk_buff {int dummy; } ;
struct nfc_dev {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
typedef  int /*<<< orphan*/  firmware_name ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_FIRMWARE_NAME ; 
 int /*<<< orphan*/  NFC_FIRMWARE_NAME_MAXSIZE ; 
 int nfc_fw_download (struct nfc_dev*,char*) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfc_genl_fw_download(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	int rc;
	u32 idx;
	char firmware_name[NFC_FIRMWARE_NAME_MAXSIZE + 1];

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		return -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		return -ENODEV;

	nla_strlcpy(firmware_name, info->attrs[NFC_ATTR_FIRMWARE_NAME],
		    sizeof(firmware_name));

	rc = nfc_fw_download(dev, firmware_name);

	nfc_put_device(dev);
	return rc;
}
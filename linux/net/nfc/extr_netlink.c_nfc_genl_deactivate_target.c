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

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_TARGET_INDEX ; 
 int /*<<< orphan*/  NFC_TARGET_MODE_SLEEP ; 
 int nfc_deactivate_target (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_deactivate_target(struct sk_buff *skb,
				      struct genl_info *info)
{
	struct nfc_dev *dev;
	u32 device_idx, target_idx;
	int rc;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_TARGET_INDEX])
		return -EINVAL;

	device_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(device_idx);
	if (!dev)
		return -ENODEV;

	target_idx = nla_get_u32(info->attrs[NFC_ATTR_TARGET_INDEX]);

	rc = nfc_deactivate_target(dev, target_idx, NFC_TARGET_MODE_SLEEP);

	nfc_put_device(dev);
	return rc;
}
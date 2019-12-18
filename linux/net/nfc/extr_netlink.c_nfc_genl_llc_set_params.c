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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_local {int /*<<< orphan*/  miux; scalar_t__ rw; void* lto; } ;
struct nfc_dev {int /*<<< orphan*/  dev; scalar_t__ dep_link_up; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ LLCP_MAX_MIUX ; 
 scalar_t__ LLCP_MAX_RW ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_LLC_PARAM_LTO ; 
 size_t NFC_ATTR_LLC_PARAM_MIUX ; 
 size_t NFC_ATTR_LLC_PARAM_RW ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 scalar_t__ nla_get_u16 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 

__attribute__((used)) static int nfc_genl_llc_set_params(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	struct nfc_llcp_local *local;
	u8 rw = 0;
	u16 miux = 0;
	u32 idx;
	int rc = 0;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    (!info->attrs[NFC_ATTR_LLC_PARAM_LTO] &&
	     !info->attrs[NFC_ATTR_LLC_PARAM_RW] &&
	     !info->attrs[NFC_ATTR_LLC_PARAM_MIUX]))
		return -EINVAL;

	if (info->attrs[NFC_ATTR_LLC_PARAM_RW]) {
		rw = nla_get_u8(info->attrs[NFC_ATTR_LLC_PARAM_RW]);

		if (rw > LLCP_MAX_RW)
			return -EINVAL;
	}

	if (info->attrs[NFC_ATTR_LLC_PARAM_MIUX]) {
		miux = nla_get_u16(info->attrs[NFC_ATTR_LLC_PARAM_MIUX]);

		if (miux > LLCP_MAX_MIUX)
			return -EINVAL;
	}

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		return -ENODEV;

	device_lock(&dev->dev);

	local = nfc_llcp_find_local(dev);
	if (!local) {
		rc = -ENODEV;
		goto exit;
	}

	if (info->attrs[NFC_ATTR_LLC_PARAM_LTO]) {
		if (dev->dep_link_up) {
			rc = -EINPROGRESS;
			goto exit;
		}

		local->lto = nla_get_u8(info->attrs[NFC_ATTR_LLC_PARAM_LTO]);
	}

	if (info->attrs[NFC_ATTR_LLC_PARAM_RW])
		local->rw = rw;

	if (info->attrs[NFC_ATTR_LLC_PARAM_MIUX])
		local->miux = cpu_to_be16(miux);

exit:
	device_unlock(&dev->dev);

	nfc_put_device(dev);

	return rc;
}
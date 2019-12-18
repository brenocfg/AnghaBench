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
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct nfc_dev {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t NFC_ATTR_COMM_MODE ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_TARGET_INDEX ; 
 scalar_t__ NFC_COMM_ACTIVE ; 
 scalar_t__ NFC_COMM_PASSIVE ; 
 int NFC_TARGET_IDX_ANY ; 
 int nfc_dep_link_up (struct nfc_dev*,int,scalar_t__) ; 
 struct nfc_dev* nfc_get_device (void*) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 void* nla_get_u32 (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int nfc_genl_dep_link_up(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	int rc, tgt_idx;
	u32 idx;
	u8 comm;

	pr_debug("DEP link up\n");

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_COMM_MODE])
		return -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	if (!info->attrs[NFC_ATTR_TARGET_INDEX])
		tgt_idx = NFC_TARGET_IDX_ANY;
	else
		tgt_idx = nla_get_u32(info->attrs[NFC_ATTR_TARGET_INDEX]);

	comm = nla_get_u8(info->attrs[NFC_ATTR_COMM_MODE]);

	if (comm != NFC_COMM_ACTIVE && comm != NFC_COMM_PASSIVE)
		return -EINVAL;

	dev = nfc_get_device(idx);
	if (!dev)
		return -ENODEV;

	rc = nfc_dep_link_up(dev, tgt_idx, comm);

	nfc_put_device(dev);

	return rc;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct se_io_ctx {void* se_idx; void* dev_idx; } ;
struct nfc_dev {TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  se_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_SE_APDU ; 
 size_t NFC_ATTR_SE_INDEX ; 
 struct se_io_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nfc_dev* nfc_get_device (void*) ; 
 int nfc_se_io (struct nfc_dev*,void*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct se_io_ctx*) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 void* nla_get_u32 (int /*<<< orphan*/ ) ; 
 size_t nla_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se_io_cb ; 

__attribute__((used)) static int nfc_genl_se_io(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	struct se_io_ctx *ctx;
	u32 dev_idx, se_idx;
	u8 *apdu;
	size_t apdu_len;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_APDU])
		return -EINVAL;

	dev_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	se_idx = nla_get_u32(info->attrs[NFC_ATTR_SE_INDEX]);

	dev = nfc_get_device(dev_idx);
	if (!dev)
		return -ENODEV;

	if (!dev->ops || !dev->ops->se_io)
		return -ENOTSUPP;

	apdu_len = nla_len(info->attrs[NFC_ATTR_SE_APDU]);
	if (apdu_len == 0)
		return -EINVAL;

	apdu = nla_data(info->attrs[NFC_ATTR_SE_APDU]);
	if (!apdu)
		return -EINVAL;

	ctx = kzalloc(sizeof(struct se_io_ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev_idx = dev_idx;
	ctx->se_idx = se_idx;

	return nfc_se_io(dev, se_idx, apdu, apdu_len, se_io_cb, ctx);
}
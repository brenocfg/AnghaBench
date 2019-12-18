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
struct nfc_llcp_local {int dummy; } ;
struct nfc_dev {int /*<<< orphan*/  dev; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 size_t NFC_ATTR_FIRMWARE_NAME ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int nfc_genl_send_params (struct sk_buff*,struct nfc_llcp_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_llc_get_params(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	struct nfc_llcp_local *local;
	int rc = 0;
	struct sk_buff *msg = NULL;
	u32 idx;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_FIRMWARE_NAME])
		return -EINVAL;

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

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		rc = -ENOMEM;
		goto exit;
	}

	rc = nfc_genl_send_params(msg, local, info->snd_portid, info->snd_seq);

exit:
	device_unlock(&dev->dev);

	nfc_put_device(dev);

	if (rc < 0) {
		if (msg)
			nlmsg_free(msg);

		return rc;
	}

	return genlmsg_reply(msg, info);
}
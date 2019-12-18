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
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int nfc_genl_send_device (struct sk_buff*,struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_get_device(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	struct nfc_dev *dev;
	u32 idx;
	int rc = -ENOBUFS;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		return -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		return -ENODEV;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		rc = -ENOMEM;
		goto out_putdev;
	}

	rc = nfc_genl_send_device(msg, dev, info->snd_portid, info->snd_seq,
				  NULL, 0);
	if (rc < 0)
		goto out_free;

	nfc_put_device(dev);

	return genlmsg_reply(msg, info);

out_free:
	nlmsg_free(msg);
out_putdev:
	nfc_put_device(dev);
	return rc;
}
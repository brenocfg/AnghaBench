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
struct sk_buff {scalar_t__ cb; } ;
struct nfc_dev {int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nfc_attrs { ____Placeholder_nfc_attrs } nfc_attrs ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  NFC_ATTR_VENDOR_ID ; 
 int /*<<< orphan*/  NFC_ATTR_VENDOR_SUBCMD ; 
 int /*<<< orphan*/  NFC_CMD_VENDOR ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* nfc_hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
__nfc_alloc_vendor_cmd_skb(struct nfc_dev *dev, int approxlen,
			   u32 portid, u32 seq,
			   enum nfc_attrs attr,
			   u32 oui, u32 subcmd, gfp_t gfp)
{
	struct sk_buff *skb;
	void *hdr;

	skb = nlmsg_new(approxlen + 100, gfp);
	if (!skb)
		return NULL;

	hdr = nfc_hdr_put(skb, portid, seq, 0, NFC_CMD_VENDOR);
	if (!hdr) {
		kfree_skb(skb);
		return NULL;
	}

	if (nla_put_u32(skb, NFC_ATTR_DEVICE_INDEX, dev->idx))
		goto nla_put_failure;
	if (nla_put_u32(skb, NFC_ATTR_VENDOR_ID, oui))
		goto nla_put_failure;
	if (nla_put_u32(skb, NFC_ATTR_VENDOR_SUBCMD, subcmd))
		goto nla_put_failure;

	((void **)skb->cb)[0] = dev;
	((void **)skb->cb)[1] = hdr;

	return skb;

nla_put_failure:
	kfree_skb(skb);
	return NULL;
}
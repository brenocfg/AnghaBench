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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nfc_dev {TYPE_1__* cur_cmd_info; } ;
typedef  enum nfc_attrs { ____Placeholder_nfc_attrs } nfc_attrs ;
struct TYPE_2__ {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 struct sk_buff* __nfc_alloc_vendor_cmd_skb (struct nfc_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sk_buff *__nfc_alloc_vendor_cmd_reply_skb(struct nfc_dev *dev,
						 enum nfc_attrs attr,
						 u32 oui, u32 subcmd,
						 int approxlen)
{
	if (WARN_ON(!dev->cur_cmd_info))
		return NULL;

	return __nfc_alloc_vendor_cmd_skb(dev, approxlen,
					  dev->cur_cmd_info->snd_portid,
					  dev->cur_cmd_info->snd_seq, attr,
					  oui, subcmd, GFP_KERNEL);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rtllib_pspoll_hdr {void* frame_ctl; void* aid; int /*<<< orphan*/  ta; int /*<<< orphan*/  bssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {int assoc_id; TYPE_2__* dev; TYPE_1__ current_network; int /*<<< orphan*/  tx_headroom; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int RTLLIB_FCTL_PM ; 
 int RTLLIB_FTYPE_CTL ; 
 int RTLLIB_STYPE_PSPOLL ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtllib_pspoll_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtllib_pspoll_func(struct rtllib_device *ieee)
{
	struct sk_buff *skb;
	struct rtllib_pspoll_hdr *hdr;

	skb = dev_alloc_skb(sizeof(struct rtllib_pspoll_hdr)+ieee->tx_headroom);
	if (!skb)
		return NULL;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, sizeof(struct rtllib_pspoll_hdr));

	ether_addr_copy(hdr->bssid, ieee->current_network.bssid);
	ether_addr_copy(hdr->ta, ieee->dev->dev_addr);

	hdr->aid = cpu_to_le16(ieee->assoc_id | 0xc000);
	hdr->frame_ctl = cpu_to_le16(RTLLIB_FTYPE_CTL | RTLLIB_STYPE_PSPOLL |
			 RTLLIB_FCTL_PM);

	return skb;

}
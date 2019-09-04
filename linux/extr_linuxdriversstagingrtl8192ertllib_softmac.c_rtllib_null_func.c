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
struct rtllib_hdr_3addr {int /*<<< orphan*/  frame_ctl; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {TYPE_2__ current_network; TYPE_1__* dev; int /*<<< orphan*/  tx_headroom; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int RTLLIB_FCTL_PM ; 
 int RTLLIB_FCTL_TODS ; 
 int RTLLIB_FTYPE_DATA ; 
 int RTLLIB_STYPE_NULLFUNC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtllib_hdr_3addr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtllib_null_func(struct rtllib_device *ieee, short pwr)
{
	struct sk_buff *skb;
	struct rtllib_hdr_3addr *hdr;

	skb = dev_alloc_skb(sizeof(struct rtllib_hdr_3addr)+ieee->tx_headroom);
	if (!skb)
		return NULL;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, sizeof(struct rtllib_hdr_3addr));

	ether_addr_copy(hdr->addr1, ieee->current_network.bssid);
	ether_addr_copy(hdr->addr2, ieee->dev->dev_addr);
	ether_addr_copy(hdr->addr3, ieee->current_network.bssid);

	hdr->frame_ctl = cpu_to_le16(RTLLIB_FTYPE_DATA |
		RTLLIB_STYPE_NULLFUNC | RTLLIB_FCTL_TODS |
		(pwr ? RTLLIB_FCTL_PM : 0));

	return skb;


}
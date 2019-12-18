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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct in6_addr {int* s6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  lltype; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  LOWPAN_IPHC_DAM_00 135 
#define  LOWPAN_IPHC_DAM_01 134 
#define  LOWPAN_IPHC_DAM_10 133 
#define  LOWPAN_IPHC_DAM_11 132 
#define  LOWPAN_IPHC_SAM_01 131 
#define  LOWPAN_IPHC_SAM_10 130 
#define  LOWPAN_IPHC_SAM_11 129 
#define  LOWPAN_LLTYPE_IEEE802154 128 
 TYPE_1__* lowpan_dev (struct net_device const*) ; 
 int lowpan_fetch_skb (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_802154_lladdr (struct in6_addr*,void const*) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_lladdr (struct net_device const*,struct in6_addr*,void const*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  raw_dump_inline (int /*<<< orphan*/ *,char*,int*,int) ; 

__attribute__((used)) static int lowpan_iphc_uncompress_addr(struct sk_buff *skb,
				       const struct net_device *dev,
				       struct in6_addr *ipaddr,
				       u8 address_mode, const void *lladdr)
{
	bool fail;

	switch (address_mode) {
	/* SAM and DAM are the same here */
	case LOWPAN_IPHC_DAM_00:
		/* for global link addresses */
		fail = lowpan_fetch_skb(skb, ipaddr->s6_addr, 16);
		break;
	case LOWPAN_IPHC_SAM_01:
	case LOWPAN_IPHC_DAM_01:
		/* fe:80::XXXX:XXXX:XXXX:XXXX */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[8], 8);
		break;
	case LOWPAN_IPHC_SAM_10:
	case LOWPAN_IPHC_DAM_10:
		/* fe:80::ff:fe00:XXXX */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		ipaddr->s6_addr[11] = 0xFF;
		ipaddr->s6_addr[12] = 0xFE;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[14], 2);
		break;
	case LOWPAN_IPHC_SAM_11:
	case LOWPAN_IPHC_DAM_11:
		fail = false;
		switch (lowpan_dev(dev)->lltype) {
		case LOWPAN_LLTYPE_IEEE802154:
			lowpan_iphc_uncompress_802154_lladdr(ipaddr, lladdr);
			break;
		default:
			lowpan_iphc_uncompress_lladdr(dev, ipaddr, lladdr);
			break;
		}
		break;
	default:
		pr_debug("Invalid address mode value: 0x%x\n", address_mode);
		return -EINVAL;
	}

	if (fail) {
		pr_debug("Failed to fetch skb data\n");
		return -EIO;
	}

	raw_dump_inline(NULL, "Reconstructed ipv6 addr is",
			ipaddr->s6_addr, 16);

	return 0;
}
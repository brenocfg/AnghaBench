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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct in6_addr {int* s6_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  LOWPAN_IPHC_DAM_00 131 
#define  LOWPAN_IPHC_DAM_01 130 
#define  LOWPAN_IPHC_DAM_10 129 
#define  LOWPAN_IPHC_DAM_11 128 
 int lowpan_fetch_skb (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  raw_dump_inline (int /*<<< orphan*/ *,char*,int*,int) ; 

__attribute__((used)) static int lowpan_uncompress_multicast_daddr(struct sk_buff *skb,
					     struct in6_addr *ipaddr,
					     u8 address_mode)
{
	bool fail;

	switch (address_mode) {
	case LOWPAN_IPHC_DAM_00:
		/* 00:  128 bits.  The full address
		 * is carried in-line.
		 */
		fail = lowpan_fetch_skb(skb, ipaddr->s6_addr, 16);
		break;
	case LOWPAN_IPHC_DAM_01:
		/* 01:  48 bits.  The address takes
		 * the form ffXX::00XX:XXXX:XXXX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[1], 1);
		fail |= lowpan_fetch_skb(skb, &ipaddr->s6_addr[11], 5);
		break;
	case LOWPAN_IPHC_DAM_10:
		/* 10:  32 bits.  The address takes
		 * the form ffXX::00XX:XXXX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[1], 1);
		fail |= lowpan_fetch_skb(skb, &ipaddr->s6_addr[13], 3);
		break;
	case LOWPAN_IPHC_DAM_11:
		/* 11:  8 bits.  The address takes
		 * the form ff02::00XX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		ipaddr->s6_addr[1] = 0x02;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[15], 1);
		break;
	default:
		pr_debug("DAM value has a wrong value: 0x%x\n", address_mode);
		return -EINVAL;
	}

	if (fail) {
		pr_debug("Failed to fetch skb data\n");
		return -EIO;
	}

	raw_dump_inline(NULL, "Reconstructed ipv6 multicast addr is",
			ipaddr->s6_addr, 16);

	return 0;
}
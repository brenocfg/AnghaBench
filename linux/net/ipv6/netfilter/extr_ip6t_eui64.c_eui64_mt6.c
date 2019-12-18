#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_action_param {scalar_t__ fragoff; int hotdrop; } ;
struct sk_buff {scalar_t__ head; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  eui64 ;
struct TYPE_6__ {scalar_t__ h_proto; scalar_t__ h_source; } ;
struct TYPE_4__ {scalar_t__ s6_addr; } ;
struct TYPE_5__ {int version; TYPE_1__ saddr; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_3__* eth_hdr (struct sk_buff const*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static bool
eui64_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	unsigned char eui64[8];

	if (!(skb_mac_header(skb) >= skb->head &&
	      skb_mac_header(skb) + ETH_HLEN <= skb->data) &&
	    par->fragoff != 0) {
		par->hotdrop = true;
		return false;
	}

	memset(eui64, 0, sizeof(eui64));

	if (eth_hdr(skb)->h_proto == htons(ETH_P_IPV6)) {
		if (ipv6_hdr(skb)->version == 0x6) {
			memcpy(eui64, eth_hdr(skb)->h_source, 3);
			memcpy(eui64 + 5, eth_hdr(skb)->h_source + 3, 3);
			eui64[3] = 0xff;
			eui64[4] = 0xfe;
			eui64[0] ^= 0x02;

			if (!memcmp(ipv6_hdr(skb)->saddr.s6_addr + 8, eui64,
				    sizeof(eui64)))
				return true;
		}
	}

	return false;
}
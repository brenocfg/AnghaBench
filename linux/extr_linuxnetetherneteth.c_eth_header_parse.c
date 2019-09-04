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
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct ethhdr* eth_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

int eth_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	const struct ethhdr *eth = eth_hdr(skb);
	memcpy(haddr, eth->h_source, ETH_ALEN);
	return ETH_ALEN;
}
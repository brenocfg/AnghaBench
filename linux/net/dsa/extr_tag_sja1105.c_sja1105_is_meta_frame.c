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
typedef  scalar_t__ u64 ;
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 scalar_t__ ETH_P_SJA1105_META ; 
 scalar_t__ SJA1105_META_DMAC ; 
 scalar_t__ SJA1105_META_SMAC ; 
 struct ethhdr* eth_hdr (struct sk_buff const*) ; 
 scalar_t__ ether_addr_to_u64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool sja1105_is_meta_frame(const struct sk_buff *skb)
{
	const struct ethhdr *hdr = eth_hdr(skb);
	u64 smac = ether_addr_to_u64(hdr->h_source);
	u64 dmac = ether_addr_to_u64(hdr->h_dest);

	if (smac != SJA1105_META_SMAC)
		return false;
	if (dmac != SJA1105_META_DMAC)
		return false;
	if (ntohs(hdr->h_proto) != ETH_P_SJA1105_META)
		return false;
	return true;
}
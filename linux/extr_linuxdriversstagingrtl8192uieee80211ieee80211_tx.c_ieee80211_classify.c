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
struct sk_buff {scalar_t__ data; } ;
struct iphdr {int tos; } ;
struct ieee80211_network {int dummy; } ;
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static int
ieee80211_classify(struct sk_buff *skb, struct ieee80211_network *network)
{
	struct ethhdr *eth;
	struct iphdr *ip;
	eth = (struct ethhdr *)skb->data;
	if (eth->h_proto != htons(ETH_P_IP))
		return 0;

	ip = ip_hdr(skb);
	switch (ip->tos & 0xfc) {
	case 0x20:
		return 2;
	case 0x40:
		return 1;
	case 0x60:
		return 3;
	case 0x80:
		return 4;
	case 0xa0:
		return 5;
	case 0xc0:
		return 6;
	case 0xe0:
		return 7;
	default:
		return 0;
	}
}
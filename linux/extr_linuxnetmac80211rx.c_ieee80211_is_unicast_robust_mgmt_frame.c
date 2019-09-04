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
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int ieee80211_is_robust_mgmt_frame (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_is_unicast_robust_mgmt_frame(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;

	if (is_multicast_ether_addr(hdr->addr1))
		return 0;

	return ieee80211_is_robust_mgmt_frame(skb);
}
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
struct sk_buff {int /*<<< orphan*/  mac_len; } ;

/* Variables and functions */
 scalar_t__ skb_at_tc_ingress (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bpf_pull_mac_rcsum(struct sk_buff *skb)
{
	if (skb_at_tc_ingress(skb))
		skb_postpull_rcsum(skb, skb_mac_header(skb), skb->mac_len);
}
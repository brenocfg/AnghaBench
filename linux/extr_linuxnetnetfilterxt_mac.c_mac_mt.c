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
struct xt_mac_info {int invert; int /*<<< orphan*/  srcaddr; } ;
struct xt_action_param {struct xt_mac_info* matchinfo; } ;
struct sk_buff {scalar_t__ head; scalar_t__ data; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_source; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ETH_HLEN ; 
 TYPE_2__* eth_hdr (struct sk_buff const*) ; 
 int ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static bool mac_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_mac_info *info = par->matchinfo;
	bool ret;

	if (skb->dev == NULL || skb->dev->type != ARPHRD_ETHER)
		return false;
	if (skb_mac_header(skb) < skb->head)
		return false;
	if (skb_mac_header(skb) + ETH_HLEN > skb->data)
		return false;
	ret  = ether_addr_equal(eth_hdr(skb)->h_source, info->srcaddr);
	ret ^= info->invert;
	return ret;
}
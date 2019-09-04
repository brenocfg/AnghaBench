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
struct xt_action_param {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  skb_checksum_help (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static unsigned int
checksum_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	if (skb->ip_summed == CHECKSUM_PARTIAL && !skb_is_gso(skb))
		skb_checksum_help(skb);

	return XT_CONTINUE;
}
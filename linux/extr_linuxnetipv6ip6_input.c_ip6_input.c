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
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_IN ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_input_finish ; 

int ip6_input(struct sk_buff *skb)
{
	return NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_IN,
		       dev_net(skb->dev), NULL, skb, skb->dev, NULL,
		       ip6_input_finish);
}
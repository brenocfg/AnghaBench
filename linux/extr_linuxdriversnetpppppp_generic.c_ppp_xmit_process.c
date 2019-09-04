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
struct ppp {int /*<<< orphan*/  dev; int /*<<< orphan*/  xmit_recursion; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ppp_xmit_process (struct ppp*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppp_xmit_process(struct ppp *ppp, struct sk_buff *skb)
{
	local_bh_disable();

	if (unlikely(*this_cpu_ptr(ppp->xmit_recursion)))
		goto err;

	(*this_cpu_ptr(ppp->xmit_recursion))++;
	__ppp_xmit_process(ppp, skb);
	(*this_cpu_ptr(ppp->xmit_recursion))--;

	local_bh_enable();

	return;

err:
	local_bh_enable();

	kfree_skb(skb);

	if (net_ratelimit())
		netdev_err(ppp->dev, "recursion detected\n");
}
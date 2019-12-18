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
struct __sk_buff {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  ingress_ifindex; int /*<<< orphan*/ * cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  hash; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int BPF_OK ; 
 int /*<<< orphan*/  CB_MAGIC ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_test_ctx(struct __sk_buff *skb)
{
	skb->cb[0] = CB_MAGIC;
	printk("len %d hash %d protocol %d\n", skb->len, skb->hash,
	       skb->protocol);
	printk("cb %d ingress_ifindex %d ifindex %d\n", skb->cb[0],
	       skb->ingress_ifindex, skb->ifindex);

	return BPF_OK;
}
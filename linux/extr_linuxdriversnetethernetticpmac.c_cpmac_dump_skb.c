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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void cpmac_dump_skb(struct net_device *dev, struct sk_buff *skb)
{
	int i;

	printk("%s: skb 0x%p, len=%d\n", dev->name, skb, skb->len);
	for (i = 0; i < skb->len; i++) {
		if (i % 16 == 0) {
			if (i)
				printk("\n");
			printk("%s: data[%p]:", dev->name, skb->data + i);
		}
		printk(" %02x", ((u8 *)skb->data)[i]);
	}
	printk("\n");
}
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
struct __sk_buff {int /*<<< orphan*/ * cb; } ;

/* Variables and functions */
 int BPF_OK ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int do_test_cb(struct __sk_buff *skb)
{
	printk("cb0: %x cb1: %x cb2: %x\n", skb->cb[0], skb->cb[1],
	       skb->cb[2]);
	printk("cb3: %x cb4: %x\n", skb->cb[3], skb->cb[4]);

	return BPF_OK;
}
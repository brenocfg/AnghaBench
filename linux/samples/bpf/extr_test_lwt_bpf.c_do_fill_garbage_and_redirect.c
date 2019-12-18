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
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int DST_IFINDEX ; 
 int /*<<< orphan*/  __fill_garbage (struct __sk_buff*) ; 
 int bpf_redirect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

int do_fill_garbage_and_redirect(struct __sk_buff *skb)
{
	int ifindex = DST_IFINDEX;
	__fill_garbage(skb);
	printk("redirected to %d\n", ifindex);
	return bpf_redirect(ifindex, 0);
}
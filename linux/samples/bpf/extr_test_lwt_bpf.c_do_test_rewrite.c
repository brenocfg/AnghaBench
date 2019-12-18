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
typedef  int uint32_t ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int BPF_DROP ; 
 int BPF_OK ; 
 int /*<<< orphan*/  IP_DST_OFF ; 
 int bpf_skb_load_bytes (struct __sk_buff*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int rewrite (struct __sk_buff*,int,int,int) ; 

int do_test_rewrite(struct __sk_buff *skb)
{
	uint32_t old_ip, new_ip = 0x3fea8c0;
	int ret;

	ret = bpf_skb_load_bytes(skb, IP_DST_OFF, &old_ip, 4);
	if (ret < 0) {
		printk("bpf_skb_load_bytes failed: %d\n", ret);
		return BPF_DROP;
	}

	if (old_ip == 0x2fea8c0) {
		printk("out: rewriting from %x to %x\n", old_ip, new_ip);
		return rewrite(skb, old_ip, new_ip, 1);
	}

	return BPF_OK;
}
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
typedef  int /*<<< orphan*/  uint64_t ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_proto; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  ehdr ;

/* Variables and functions */
 int BPF_DROP ; 
 int DST_IFINDEX ; 
 int /*<<< orphan*/  DST_MAC ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  SRC_MAC ; 
 int /*<<< orphan*/  __constant_htons (int /*<<< orphan*/ ) ; 
 int bpf_redirect (int,int /*<<< orphan*/ ) ; 
 int bpf_skb_change_head (struct __sk_buff*,int,int /*<<< orphan*/ ) ; 
 int bpf_skb_store_bytes (struct __sk_buff*,int /*<<< orphan*/ ,struct ethhdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static inline int __do_push_ll_and_redirect(struct __sk_buff *skb)
{
	uint64_t smac = SRC_MAC, dmac = DST_MAC;
	int ret, ifindex = DST_IFINDEX;
	struct ethhdr ehdr;

	ret = bpf_skb_change_head(skb, 14, 0);
	if (ret < 0) {
		printk("skb_change_head() failed: %d\n", ret);
	}

	ehdr.h_proto = __constant_htons(ETH_P_IP);
	memcpy(&ehdr.h_source, &smac, 6);
	memcpy(&ehdr.h_dest, &dmac, 6);

	ret = bpf_skb_store_bytes(skb, 0, &ehdr, sizeof(ehdr), 0);
	if (ret < 0) {
		printk("skb_store_bytes() failed: %d\n", ret);
		return BPF_DROP;
	}

	return bpf_redirect(ifindex, 0);
}
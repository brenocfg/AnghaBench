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
struct tcphdr {int dummy; } ;
struct iphdr {int ihl; scalar_t__ protocol; } ;
struct ethhdr {int dummy; } ;
struct __sk_buff {scalar_t__ data; scalar_t__ data_end; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 int handle_tcp (struct __sk_buff*,struct tcphdr*) ; 

__attribute__((used)) static inline int handle_ipv4(struct __sk_buff *skb)
{
	void *data_end = (void *)(long)skb->data_end;
	void *data = (void *)(long)skb->data;
	struct iphdr *iph;
	uint32_t ihl;

	/* drop malformed packets */
	if (data + sizeof(struct ethhdr) > data_end)
		return TC_ACT_SHOT;
	iph = (struct iphdr *)(data + sizeof(struct ethhdr));
	if ((void *)(iph + 1) > data_end)
		return TC_ACT_SHOT;
	ihl = iph->ihl * 4;
	if (((void *)iph) + ihl > data_end)
		return TC_ACT_SHOT;

	if (iph->protocol == IPPROTO_TCP)
		return handle_tcp(skb, (struct tcphdr *)(((void *)iph) + ihl));

	return TC_ACT_OK;
}
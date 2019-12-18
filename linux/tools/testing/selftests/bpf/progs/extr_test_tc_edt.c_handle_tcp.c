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
struct tcphdr {scalar_t__ dest; } ;
struct __sk_buff {scalar_t__ data_end; } ;

/* Variables and functions */
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 scalar_t__ bpf_htons (int) ; 
 int throttle_flow (struct __sk_buff*) ; 

__attribute__((used)) static inline int handle_tcp(struct __sk_buff *skb, struct tcphdr *tcp)
{
	void *data_end = (void *)(long)skb->data_end;

	/* drop malformed packets */
	if ((void *)(tcp + 1) > data_end)
		return TC_ACT_SHOT;

	if (tcp->dest == bpf_htons(9000))
		return throttle_flow(skb);

	return TC_ACT_OK;
}
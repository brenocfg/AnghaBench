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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  load_half (struct __sk_buff*,int) ; 
 int /*<<< orphan*/  parse_eth_proto (struct __sk_buff*,int /*<<< orphan*/ ) ; 

int main_prog(struct __sk_buff *skb)
{
	__u32 nhoff = ETH_HLEN;
	__u32 proto = load_half(skb, 12);

	skb->cb[0] = nhoff;
	parse_eth_proto(skb, proto);
	return 0;
}
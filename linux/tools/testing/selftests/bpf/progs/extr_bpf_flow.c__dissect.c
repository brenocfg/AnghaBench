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
struct bpf_flow_keys {int /*<<< orphan*/  n_proto; } ;
struct __sk_buff {struct bpf_flow_keys* flow_keys; } ;

/* Variables and functions */
 int parse_eth_proto (struct __sk_buff*,int /*<<< orphan*/ ) ; 

int _dissect(struct __sk_buff *skb)
{
	struct bpf_flow_keys *keys = skb->flow_keys;

	return parse_eth_proto(skb, keys->n_proto);
}
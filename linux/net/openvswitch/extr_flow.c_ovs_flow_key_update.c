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
struct sw_flow_key {int /*<<< orphan*/  mac_proto; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_FLOW_KEY_INVALID ; 
 int key_extract (struct sk_buff*,struct sw_flow_key*) ; 

int ovs_flow_key_update(struct sk_buff *skb, struct sw_flow_key *key)
{
	int res;

	res = key_extract(skb, key);
	if (!res)
		key->mac_proto &= ~SW_FLOW_KEY_INVALID;

	return res;
}
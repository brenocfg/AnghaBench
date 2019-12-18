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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int key_extract_l3l4 (struct sk_buff*,struct sw_flow_key*) ; 

int ovs_flow_key_update_l3l4(struct sk_buff *skb, struct sw_flow_key *key)
{
	return key_extract_l3l4(skb, key);
}
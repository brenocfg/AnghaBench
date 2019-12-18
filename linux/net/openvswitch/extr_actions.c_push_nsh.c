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
struct nshhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PROTO_NONE ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int nsh_push (struct sk_buff*,struct nshhdr const*) ; 

__attribute__((used)) static int push_nsh(struct sk_buff *skb, struct sw_flow_key *key,
		    const struct nshhdr *nh)
{
	int err;

	err = nsh_push(skb, nh);
	if (err)
		return err;

	/* safe right before invalidate_flow_key */
	key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	return 0;
}
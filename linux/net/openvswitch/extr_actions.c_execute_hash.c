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
typedef  int u32 ;
struct sw_flow_key {int ovs_flow_hash; } ;
struct sk_buff {int dummy; } ;
struct ovs_action_hash {int /*<<< orphan*/  hash_basis; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int jhash_1word (int,int /*<<< orphan*/ ) ; 
 struct ovs_action_hash* nla_data (struct nlattr const*) ; 
 int skb_get_hash (struct sk_buff*) ; 

__attribute__((used)) static void execute_hash(struct sk_buff *skb, struct sw_flow_key *key,
			 const struct nlattr *attr)
{
	struct ovs_action_hash *hash_act = nla_data(attr);
	u32 hash = 0;

	/* OVS_HASH_ALG_L4 is the only possible hash algorithm.  */
	hash = skb_get_hash(skb);
	hash = jhash_1word(hash, hash_act->hash_basis);
	if (!hash)
		hash = 0x1;

	key->ovs_flow_hash = hash;
}
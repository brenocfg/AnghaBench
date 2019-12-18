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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct flow_keys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___skb_get_hash (struct sk_buff*,struct flow_keys*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __flow_hash_secret_init () ; 
 int /*<<< orphan*/  __skb_set_sw_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_keys_have_l4 (struct flow_keys*) ; 
 int /*<<< orphan*/  hashrnd ; 

void __skb_get_hash(struct sk_buff *skb)
{
	struct flow_keys keys;
	u32 hash;

	__flow_hash_secret_init();

	hash = ___skb_get_hash(skb, &keys, &hashrnd);

	__skb_set_sw_hash(skb, hash, flow_keys_have_l4(&keys));
}
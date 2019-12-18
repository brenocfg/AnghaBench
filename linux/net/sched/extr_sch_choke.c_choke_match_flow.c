#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ protocol; } ;
struct flow_keys {int dummy; } ;
struct TYPE_2__ {int keys_valid; int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 TYPE_1__* choke_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  make_flow_keys_digest (int /*<<< orphan*/ *,struct flow_keys*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_flow_dissect_flow_keys (struct sk_buff*,struct flow_keys*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool choke_match_flow(struct sk_buff *skb1,
			     struct sk_buff *skb2)
{
	struct flow_keys temp;

	if (skb1->protocol != skb2->protocol)
		return false;

	if (!choke_skb_cb(skb1)->keys_valid) {
		choke_skb_cb(skb1)->keys_valid = 1;
		skb_flow_dissect_flow_keys(skb1, &temp, 0);
		make_flow_keys_digest(&choke_skb_cb(skb1)->keys, &temp);
	}

	if (!choke_skb_cb(skb2)->keys_valid) {
		choke_skb_cb(skb2)->keys_valid = 1;
		skb_flow_dissect_flow_keys(skb2, &temp, 0);
		make_flow_keys_digest(&choke_skb_cb(skb2)->keys, &temp);
	}

	return !memcmp(&choke_skb_cb(skb1)->keys,
		       &choke_skb_cb(skb2)->keys,
		       sizeof(choke_skb_cb(skb1)->keys));
}
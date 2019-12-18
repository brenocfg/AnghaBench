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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct flow_keys_basic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_get_poff (struct sk_buff const*,int /*<<< orphan*/ ,struct flow_keys_basic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_flow_dissect_flow_keys_basic (int /*<<< orphan*/ *,struct sk_buff const*,struct flow_keys_basic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff const*) ; 

u32 skb_get_poff(const struct sk_buff *skb)
{
	struct flow_keys_basic keys;

	if (!skb_flow_dissect_flow_keys_basic(NULL, skb, &keys,
					      NULL, 0, 0, 0, 0))
		return 0;

	return __skb_get_poff(skb, skb->data, &keys, skb_headlen(skb));
}
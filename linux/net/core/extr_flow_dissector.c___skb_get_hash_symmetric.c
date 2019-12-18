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
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL ; 
 int /*<<< orphan*/  __flow_hash_from_keys (struct flow_keys*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __flow_hash_secret_init () ; 
 int /*<<< orphan*/  __skb_flow_dissect (int /*<<< orphan*/ *,struct sk_buff const*,int /*<<< orphan*/ *,struct flow_keys*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_keys_dissector_symmetric ; 
 int /*<<< orphan*/  hashrnd ; 
 int /*<<< orphan*/  memset (struct flow_keys*,int /*<<< orphan*/ ,int) ; 

u32 __skb_get_hash_symmetric(const struct sk_buff *skb)
{
	struct flow_keys keys;

	__flow_hash_secret_init();

	memset(&keys, 0, sizeof(keys));
	__skb_flow_dissect(NULL, skb, &flow_keys_dissector_symmetric,
			   &keys, NULL, 0, 0, 0,
			   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	return __flow_hash_from_keys(&keys, &hashrnd);
}
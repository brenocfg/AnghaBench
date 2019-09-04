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
struct flow_dissector_key {scalar_t__ offset; size_t key_id; } ;
struct flow_dissector {scalar_t__* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t FLOW_DISSECTOR_KEY_BASIC ; 
 size_t FLOW_DISSECTOR_KEY_CONTROL ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  dissector_set_key (struct flow_dissector*,size_t) ; 
 int dissector_uses_key (struct flow_dissector*,size_t) ; 
 int /*<<< orphan*/  memset (struct flow_dissector*,int /*<<< orphan*/ ,int) ; 

void skb_flow_dissector_init(struct flow_dissector *flow_dissector,
			     const struct flow_dissector_key *key,
			     unsigned int key_count)
{
	unsigned int i;

	memset(flow_dissector, 0, sizeof(*flow_dissector));

	for (i = 0; i < key_count; i++, key++) {
		/* User should make sure that every key target offset is withing
		 * boundaries of unsigned short.
		 */
		BUG_ON(key->offset > USHRT_MAX);
		BUG_ON(dissector_uses_key(flow_dissector,
					  key->key_id));

		dissector_set_key(flow_dissector, key->key_id);
		flow_dissector->offset[key->key_id] = key->offset;
	}

	/* Ensure that the dissector always includes control and basic key.
	 * That way we are able to avoid handling lack of these in fast path.
	 */
	BUG_ON(!dissector_uses_key(flow_dissector,
				   FLOW_DISSECTOR_KEY_CONTROL));
	BUG_ON(!dissector_uses_key(flow_dissector,
				   FLOW_DISSECTOR_KEY_BASIC));
}
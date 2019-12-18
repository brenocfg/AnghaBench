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
struct sk_buff {int dummy; } ;
struct flow_dissector_key_vlan {scalar_t__ vlan_priority; scalar_t__ vlan_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memchr_inv (struct flow_dissector_key_vlan*,int /*<<< orphan*/ ,int) ; 
 int nla_put_u16 (struct sk_buff*,int,scalar_t__) ; 
 int nla_put_u8 (struct sk_buff*,int,scalar_t__) ; 

__attribute__((used)) static int fl_dump_key_vlan(struct sk_buff *skb,
			    int vlan_id_key, int vlan_prio_key,
			    struct flow_dissector_key_vlan *vlan_key,
			    struct flow_dissector_key_vlan *vlan_mask)
{
	int err;

	if (!memchr_inv(vlan_mask, 0, sizeof(*vlan_mask)))
		return 0;
	if (vlan_mask->vlan_id) {
		err = nla_put_u16(skb, vlan_id_key,
				  vlan_key->vlan_id);
		if (err)
			return err;
	}
	if (vlan_mask->vlan_priority) {
		err = nla_put_u8(skb, vlan_prio_key,
				 vlan_key->vlan_priority);
		if (err)
			return err;
	}
	return 0;
}
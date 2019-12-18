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
typedef  scalar_t__ u16 ;
struct rhashtable_compare_arg {scalar_t__ key; } ;
struct net_bridge_vlan {scalar_t__ vid; } ;

/* Variables and functions */

__attribute__((used)) static inline int br_vlan_cmp(struct rhashtable_compare_arg *arg,
			      const void *ptr)
{
	const struct net_bridge_vlan *vle = ptr;
	u16 vid = *(u16 *)arg->key;

	return vle->vid != vid;
}
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
struct rhashtable_compare_arg {scalar_t__ key; } ;
struct TYPE_2__ {scalar_t__ tunnel_id; } ;
struct net_bridge_vlan {TYPE_1__ tinfo; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */

__attribute__((used)) static inline int br_vlan_tunid_cmp(struct rhashtable_compare_arg *arg,
				    const void *ptr)
{
	const struct net_bridge_vlan *vle = ptr;
	__be64 tunid = *(__be64 *)arg->key;

	return vle->tinfo.tunnel_id != tunid;
}
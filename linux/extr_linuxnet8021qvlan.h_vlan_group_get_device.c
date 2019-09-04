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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct net_device* __vlan_group_get_device (struct vlan_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_proto_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct net_device *vlan_group_get_device(struct vlan_group *vg,
						       __be16 vlan_proto,
						       u16 vlan_id)
{
	return __vlan_group_get_device(vg, vlan_proto_idx(vlan_proto), vlan_id);
}
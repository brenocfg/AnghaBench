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
struct net_device {int dummy; } ;
struct batadv_softif_vlan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int batadv_sysfs_add_vlan(struct net_device *dev,
					struct batadv_softif_vlan *vlan)
{
	return 0;
}
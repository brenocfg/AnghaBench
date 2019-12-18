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
struct net_device {int dummy; } ;
struct br_vlan_bind_walk_data {scalar_t__ vid; struct net_device* result; } ;
struct TYPE_2__ {scalar_t__ vlan_id; } ;

/* Variables and functions */
 scalar_t__ br_vlan_is_bind_vlan_dev (struct net_device*) ; 
 TYPE_1__* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static int br_vlan_match_bind_vlan_dev_fn(struct net_device *dev,
					  void *data_in)
{
	struct br_vlan_bind_walk_data *data = data_in;
	int found = 0;

	if (br_vlan_is_bind_vlan_dev(dev) &&
	    vlan_dev_priv(dev)->vlan_id == data->vid) {
		data->result = dev;
		found = 1;
	}

	return found;
}
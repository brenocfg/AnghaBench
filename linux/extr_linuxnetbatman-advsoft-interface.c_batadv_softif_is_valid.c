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
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {scalar_t__ ndo_start_xmit; } ;

/* Variables and functions */
 scalar_t__ batadv_interface_tx ; 

bool batadv_softif_is_valid(const struct net_device *net_dev)
{
	if (net_dev->netdev_ops->ndo_start_xmit == batadv_interface_tx)
		return true;

	return false;
}
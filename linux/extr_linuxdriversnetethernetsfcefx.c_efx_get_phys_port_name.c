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
struct efx_nic {int port_num; } ;

/* Variables and functions */
 int EINVAL ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 size_t snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int efx_get_phys_port_name(struct net_device *net_dev,
				  char *name, size_t len)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (snprintf(name, len, "p%u", efx->port_num) >= len)
		return -EINVAL;
	return 0;
}
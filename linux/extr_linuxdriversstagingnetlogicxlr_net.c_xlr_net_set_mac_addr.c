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

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  xlr_hw_set_mac_addr (struct net_device*) ; 

__attribute__((used)) static int xlr_net_set_mac_addr(struct net_device *ndev, void *data)
{
	int err;

	err = eth_mac_addr(ndev, data);
	if (err)
		return err;
	xlr_hw_set_mac_addr(ndev);
	return 0;
}
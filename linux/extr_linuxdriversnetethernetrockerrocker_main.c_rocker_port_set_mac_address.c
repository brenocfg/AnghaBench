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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct rocker_port {int dummy; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int rocker_cmd_set_port_settings_macaddr (struct rocker_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_port_set_mac_address(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct rocker_port *rocker_port = netdev_priv(dev);
	int err;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	err = rocker_cmd_set_port_settings_macaddr(rocker_port, addr->sa_data);
	if (err)
		return err;
	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	return 0;
}
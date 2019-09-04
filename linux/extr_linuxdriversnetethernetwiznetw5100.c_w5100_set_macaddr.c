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
struct w5100_priv {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  w5100_write_macaddr (struct w5100_priv*) ; 

__attribute__((used)) static int w5100_set_macaddr(struct net_device *ndev, void *addr)
{
	struct w5100_priv *priv = netdev_priv(ndev);
	struct sockaddr *sock_addr = addr;

	if (!is_valid_ether_addr(sock_addr->sa_data))
		return -EADDRNOTAVAIL;
	memcpy(ndev->dev_addr, sock_addr->sa_data, ETH_ALEN);
	w5100_write_macaddr(priv);
	return 0;
}
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
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAHR ; 
 int /*<<< orphan*/  MALR ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_mac_address(struct net_device *ndev)
{
	sh_eth_write(ndev,
		     (ndev->dev_addr[0] << 24) | (ndev->dev_addr[1] << 16) |
		     (ndev->dev_addr[2] << 8) | (ndev->dev_addr[3]), MAHR);
	sh_eth_write(ndev,
		     (ndev->dev_addr[4] << 8) | (ndev->dev_addr[5]), MALR);
}
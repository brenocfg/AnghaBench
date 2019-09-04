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
struct tsi108_prv_data {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_write_mii (struct tsi108_prv_data*,int,int) ; 

__attribute__((used)) static void tsi108_mdio_write(struct net_device *dev, int addr, int reg, int val)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	tsi108_write_mii(data, reg, val);
}
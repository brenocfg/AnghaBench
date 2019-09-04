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
typedef  void* u8 ;
typedef  int u32 ;
struct smsc911x_data {int dummy; } ;
struct net_device {void** dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRH ; 
 int /*<<< orphan*/  ADDRL ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsc911x_read_mac_address(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	u32 mac_high16 = smsc911x_mac_read(pdata, ADDRH);
	u32 mac_low32 = smsc911x_mac_read(pdata, ADDRL);

	dev->dev_addr[0] = (u8)(mac_low32);
	dev->dev_addr[1] = (u8)(mac_low32 >> 8);
	dev->dev_addr[2] = (u8)(mac_low32 >> 16);
	dev->dev_addr[3] = (u8)(mac_low32 >> 24);
	dev->dev_addr[4] = (u8)(mac_high16);
	dev->dev_addr[5] = (u8)(mac_high16 >> 8);
}
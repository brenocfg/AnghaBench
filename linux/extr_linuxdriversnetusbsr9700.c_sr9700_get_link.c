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
typedef  int u8 ;
typedef  int u32 ;
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NSR_LINKST ; 
 int /*<<< orphan*/  SR_NSR ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sr_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32 sr9700_get_link(struct net_device *netdev)
{
	struct usbnet *dev = netdev_priv(netdev);
	u8 value = 0;
	int rc = 0;

	/* Get the Link Status directly */
	sr_read_reg(dev, SR_NSR, &value);
	if (value & NSR_LINKST)
		rc = 1;

	return rc;
}
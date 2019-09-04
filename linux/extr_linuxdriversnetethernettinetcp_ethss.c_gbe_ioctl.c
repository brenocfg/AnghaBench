#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_2__* drv; } ;
struct ifreq {int dummy; } ;
struct gbe_intf {TYPE_1__* slave; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwtstamp; } ;
struct TYPE_3__ {struct phy_device* phy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int gbe_hwtstamp_get (struct gbe_intf*,struct ifreq*) ; 
 int gbe_hwtstamp_set (struct gbe_intf*,struct ifreq*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 

__attribute__((used)) static int gbe_ioctl(void *intf_priv, struct ifreq *req, int cmd)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct phy_device *phy = gbe_intf->slave->phy;

	if (!phy || !phy->drv->hwtstamp) {
		switch (cmd) {
		case SIOCGHWTSTAMP:
			return gbe_hwtstamp_get(gbe_intf, req);
		case SIOCSHWTSTAMP:
			return gbe_hwtstamp_set(gbe_intf, req);
		}
	}

	if (phy)
		return phy_mii_ioctl(phy, req, cmd);

	return -EOPNOTSUPP;
}
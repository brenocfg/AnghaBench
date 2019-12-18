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
typedef  int u16 ;
struct switch_port_link {int speed; scalar_t__ duplex; scalar_t__ aneg; } ;
struct switch_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_write16 ) (struct switch_dev*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  SWITCH_PORT_SPEED_10 130 
#define  SWITCH_PORT_SPEED_100 129 
#define  SWITCH_PORT_SPEED_1000 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct switch_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct switch_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct switch_dev*,int,int /*<<< orphan*/ ,int) ; 

int
switch_generic_set_link(struct switch_dev *dev, int port,
			struct switch_port_link *link)
{
	if (WARN_ON(!dev->ops->phy_write16))
		return -ENOTSUPP;

	/* Generic implementation */
	if (link->aneg) {
		dev->ops->phy_write16(dev, port, MII_BMCR, 0x0000);
		dev->ops->phy_write16(dev, port, MII_BMCR, BMCR_ANENABLE | BMCR_ANRESTART);
	} else {
		u16 bmcr = 0;

		if (link->duplex)
			bmcr |= BMCR_FULLDPLX;

		switch (link->speed) {
		case SWITCH_PORT_SPEED_10:
			break;
		case SWITCH_PORT_SPEED_100:
			bmcr |= BMCR_SPEED100;
			break;
		case SWITCH_PORT_SPEED_1000:
			bmcr |= BMCR_SPEED1000;
			break;
		default:
			return -ENOTSUPP;
		}

		dev->ops->phy_write16(dev, port, MII_BMCR, bmcr);
	}

	return 0;
}
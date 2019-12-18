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
struct switch_port_link {int /*<<< orphan*/  speed; void* aneg; void* duplex; void* link; } ;
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX ; 
 int EINVAL ; 
 int /*<<< orphan*/  LINK ; 
 int /*<<< orphan*/  NWAY ; 
 int RTL8306_NUM_PORTS ; 
 int /*<<< orphan*/  RTL_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_10 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_100 ; 
 void* rtl_get (struct switch_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
rtl_get_port_link(struct switch_dev *dev, int port, struct switch_port_link *link)
{
	if (port >= RTL8306_NUM_PORTS)
		return -EINVAL;

	/* in case the link changes from down to up, the register is only updated on read */
	link->link = rtl_get(dev, RTL_PORT_REG(port, LINK));
	if (!link->link)
		link->link = rtl_get(dev, RTL_PORT_REG(port, LINK));

	if (!link->link)
		return 0;

	link->duplex = rtl_get(dev, RTL_PORT_REG(port, DUPLEX));
	link->aneg = rtl_get(dev, RTL_PORT_REG(port, NWAY));

	if (rtl_get(dev, RTL_PORT_REG(port, SPEED)))
		link->speed = SWITCH_PORT_SPEED_100;
	else
		link->speed = SWITCH_PORT_SPEED_10;

	return 0;
}
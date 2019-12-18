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
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NRESTART ; 
 int /*<<< orphan*/  RTL_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXEN ; 
 int /*<<< orphan*/  TXEN ; 
 int /*<<< orphan*/  rtl_set (struct switch_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtl_port_set_enable(struct switch_dev *dev, int port, int enabled)
{
	rtl_set(dev, RTL_PORT_REG(port, RXEN), enabled);
	rtl_set(dev, RTL_PORT_REG(port, TXEN), enabled);

	if ((port >= 5) || !enabled)
		return;

	/* restart autonegotiation if enabled */
	rtl_set(dev, RTL_PORT_REG(port, NRESTART), 1);
}
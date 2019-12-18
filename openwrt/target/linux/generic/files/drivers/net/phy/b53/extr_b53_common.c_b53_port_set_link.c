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
struct switch_port_link {scalar_t__ speed; int /*<<< orphan*/  duplex; } ;
struct switch_dev {int cpu_port; } ;
struct b53_device {int enabled_ports; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ SWITCH_PORT_SPEED_1000 ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 scalar_t__ is63xx (struct b53_device*) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 
 int switch_generic_set_link (struct switch_dev*,int,struct switch_port_link*) ; 

__attribute__((used)) static int b53_port_set_link(struct switch_dev *sw_dev, int port,
			     struct switch_port_link *link)
{
	struct b53_device *dev = sw_to_b53(sw_dev);

	/*
	 * TODO: BCM63XX requires special handling as it can have external phys
	 * and ports might be GE or only FE
	 */
	if (is63xx(dev))
		return -ENOTSUPP;

	if (port == sw_dev->cpu_port)
		return -EINVAL;

	if (!(BIT(port) & dev->enabled_ports))
		return -EINVAL;

	if (link->speed == SWITCH_PORT_SPEED_1000 &&
	    (is5325(dev) || is5365(dev)))
		return -EINVAL;

	if (link->speed == SWITCH_PORT_SPEED_1000 && !link->duplex)
		return -EINVAL;

	return switch_generic_set_link(sw_dev, port, link);
}
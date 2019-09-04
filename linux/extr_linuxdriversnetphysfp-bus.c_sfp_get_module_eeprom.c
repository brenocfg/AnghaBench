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
typedef  int /*<<< orphan*/  u8 ;
struct sfp_bus {int /*<<< orphan*/  sfp; TYPE_1__* socket_ops; } ;
struct ethtool_eeprom {int dummy; } ;
struct TYPE_2__ {int (* module_eeprom ) (int /*<<< orphan*/ ,struct ethtool_eeprom*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct ethtool_eeprom*,int /*<<< orphan*/ *) ; 

int sfp_get_module_eeprom(struct sfp_bus *bus, struct ethtool_eeprom *ee,
			  u8 *data)
{
	return bus->socket_ops->module_eeprom(bus->sfp, ee, data);
}
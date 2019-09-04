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
struct sfp_upstream_ops {int (* module_insert ) (int /*<<< orphan*/ ,struct sfp_eeprom_id const*) ;} ;
struct sfp_eeprom_id {int dummy; } ;
struct sfp_bus {int /*<<< orphan*/  upstream; } ;

/* Variables and functions */
 struct sfp_upstream_ops* sfp_get_upstream_ops (struct sfp_bus*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sfp_eeprom_id const*) ; 

int sfp_module_insert(struct sfp_bus *bus, const struct sfp_eeprom_id *id)
{
	const struct sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);
	int ret = 0;

	if (ops && ops->module_insert)
		ret = ops->module_insert(bus->upstream, id);

	return ret;
}
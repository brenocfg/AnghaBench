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
struct net_device {int dummy; } ;
struct dsa_switch {TYPE_2__* ops; TYPE_1__* cd; } ;
struct dsa_port {struct dsa_switch* ds; } ;
struct TYPE_4__ {int (* get_eeprom_len ) (struct dsa_switch*) ;} ;
struct TYPE_3__ {int eeprom_len; } ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int stub1 (struct dsa_switch*) ; 

__attribute__((used)) static int dsa_slave_get_eeprom_len(struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	if (ds->cd && ds->cd->eeprom_len)
		return ds->cd->eeprom_len;

	if (ds->ops->get_eeprom_len)
		return ds->ops->get_eeprom_len(ds);

	return 0;
}
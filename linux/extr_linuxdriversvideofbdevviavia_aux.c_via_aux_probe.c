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
struct via_aux_bus {int /*<<< orphan*/  drivers; struct i2c_adapter* adap; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct via_aux_bus* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_aux_ch7301_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_edid_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_sii164_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1621_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1622_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1625_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1631_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1632_probe (struct via_aux_bus*) ; 
 int /*<<< orphan*/  via_aux_vt1636_probe (struct via_aux_bus*) ; 

struct via_aux_bus *via_aux_probe(struct i2c_adapter *adap)
{
	struct via_aux_bus *bus;

	if (!adap)
		return NULL;

	bus = kmalloc(sizeof(*bus), GFP_KERNEL);
	if (!bus)
		return NULL;

	bus->adap = adap;
	INIT_LIST_HEAD(&bus->drivers);

	via_aux_edid_probe(bus);
	via_aux_vt1636_probe(bus);
	via_aux_vt1632_probe(bus);
	via_aux_vt1631_probe(bus);
	via_aux_vt1625_probe(bus);
	via_aux_vt1622_probe(bus);
	via_aux_vt1621_probe(bus);
	via_aux_sii164_probe(bus);
	via_aux_ch7301_probe(bus);

	return bus;
}
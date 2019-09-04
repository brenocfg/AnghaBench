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
struct power_supply_config {struct gb_power_supply* drv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  property_is_writeable; int /*<<< orphan*/  set_property; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct gb_power_supply {int /*<<< orphan*/  psy; TYPE_2__ desc; int /*<<< orphan*/  props_raw; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 int /*<<< orphan*/  get_property ; 
 int /*<<< orphan*/  power_supply_register (int /*<<< orphan*/ *,TYPE_2__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  property_is_writeable ; 
 int /*<<< orphan*/  set_property ; 
 int /*<<< orphan*/  total_props (struct gb_power_supply*) ; 

__attribute__((used)) static int gb_power_supply_register(struct gb_power_supply *gbpsy)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	struct power_supply_config cfg = {};

	cfg.drv_data = gbpsy;

	gbpsy->desc.name		= gbpsy->name;
	gbpsy->desc.type		= gbpsy->type;
	gbpsy->desc.properties		= gbpsy->props_raw;
	gbpsy->desc.num_properties	= total_props(gbpsy);
	gbpsy->desc.get_property	= get_property;
	gbpsy->desc.set_property	= set_property;
	gbpsy->desc.property_is_writeable = property_is_writeable;

	gbpsy->psy = power_supply_register(&connection->bundle->dev,
					   &gbpsy->desc, &cfg);
	return PTR_ERR_OR_ZERO(gbpsy->psy);
}
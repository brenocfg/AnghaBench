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
struct gb_power_supply_set_property_request {int /*<<< orphan*/  prop_val; int /*<<< orphan*/  property; int /*<<< orphan*/  psy_id; } ;
struct gb_power_supply_prop {int val; int /*<<< orphan*/  gb_prop; } ;
struct gb_power_supply {int /*<<< orphan*/  id; } ;
struct gb_connection {int /*<<< orphan*/  bundle; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  req ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_POWER_SUPPLY_TYPE_SET_PROPERTY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_power_supply_set_property_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 struct gb_power_supply_prop* get_psy_prop (struct gb_power_supply*,int) ; 

__attribute__((used)) static int gb_power_supply_property_set(struct gb_power_supply *gbpsy,
					enum power_supply_property psp,
					int val)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	struct gb_power_supply_prop *prop;
	struct gb_power_supply_set_property_request req;
	int ret;

	ret = gb_pm_runtime_get_sync(connection->bundle);
	if (ret)
		return ret;

	prop = get_psy_prop(gbpsy, psp);
	if (!prop) {
		ret = -EINVAL;
		goto out;
	}

	req.psy_id = gbpsy->id;
	req.property = prop->gb_prop;
	req.prop_val = cpu_to_le32((s32)val);

	ret = gb_operation_sync(connection, GB_POWER_SUPPLY_TYPE_SET_PROPERTY,
				&req, sizeof(req), NULL, 0);
	if (ret < 0)
		goto out;

	/* cache immediately the new value */
	prop->val = val;

out:
	gb_pm_runtime_put_autosuspend(connection->bundle);
	return ret;
}
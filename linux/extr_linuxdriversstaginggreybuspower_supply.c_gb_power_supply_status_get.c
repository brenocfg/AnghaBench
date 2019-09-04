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
struct gb_power_supply {int properties_count; int /*<<< orphan*/  last_update; TYPE_1__* props; } ;
struct gb_connection {int /*<<< orphan*/  bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  prop; } ;

/* Variables and functions */
 int __gb_power_supply_property_update (struct gb_power_supply*,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 scalar_t__ is_cache_valid (struct gb_power_supply*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int gb_power_supply_status_get(struct gb_power_supply *gbpsy)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	int ret = 0;
	int i;

	if (is_cache_valid(gbpsy))
		return 0;

	ret = gb_pm_runtime_get_sync(connection->bundle);
	if (ret)
		return ret;

	for (i = 0; i < gbpsy->properties_count; i++) {
		ret = __gb_power_supply_property_update(gbpsy,
							gbpsy->props[i].prop);
		if (ret < 0)
			break;
	}

	if (ret == 0)
		gbpsy->last_update = jiffies;

	gb_pm_runtime_put_autosuspend(connection->bundle);
	return ret;
}
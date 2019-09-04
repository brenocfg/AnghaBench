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
struct gb_power_supply {int dummy; } ;
struct gb_power_supplies {int supplies_count; int /*<<< orphan*/  supplies_lock; int /*<<< orphan*/  supply; struct gb_connection* connection; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_power_supplies_get_count (struct gb_power_supplies*) ; 
 int gb_power_supply_config (struct gb_power_supplies*,int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_power_supplies_setup(struct gb_power_supplies *supplies)
{
	struct gb_connection *connection = supplies->connection;
	int ret;
	int i;

	mutex_lock(&supplies->supplies_lock);

	ret = gb_power_supplies_get_count(supplies);
	if (ret < 0)
		goto out;

	supplies->supply = kcalloc(supplies->supplies_count,
				     sizeof(struct gb_power_supply),
				     GFP_KERNEL);

	if (!supplies->supply) {
		ret = -ENOMEM;
		goto out;
	}

	for (i = 0; i < supplies->supplies_count; i++) {
		ret = gb_power_supply_config(supplies, i);
		if (ret < 0) {
			dev_err(&connection->bundle->dev,
				"Fail to configure supplies devices\n");
			goto out;
		}
	}
out:
	mutex_unlock(&supplies->supplies_lock);
	return ret;
}
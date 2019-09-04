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
struct regulator_supply_alias {char* alias_supply; struct device* alias_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct regulator_supply_alias* regulator_find_supply_alias (struct device*,char const*) ; 

__attribute__((used)) static void regulator_supply_alias(struct device **dev, const char **supply)
{
	struct regulator_supply_alias *map;

	map = regulator_find_supply_alias(*dev, *supply);
	if (map) {
		dev_dbg(*dev, "Mapping supply %s to %s,%s\n",
				*supply, map->alias_supply,
				dev_name(map->alias_dev));
		*dev = map->alias_dev;
		*supply = map->alias_supply;
	}
}
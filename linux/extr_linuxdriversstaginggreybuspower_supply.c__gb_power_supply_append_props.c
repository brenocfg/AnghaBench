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
struct gb_power_supply {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_PROP_MANUFACTURER ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_MODEL_NAME ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_SERIAL_NUMBER ; 
 int /*<<< orphan*/  prop_append (struct gb_power_supply*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _gb_power_supply_append_props(struct gb_power_supply *gbpsy)
{
	if (strlen(gbpsy->manufacturer))
		prop_append(gbpsy, POWER_SUPPLY_PROP_MANUFACTURER);
	if (strlen(gbpsy->model_name))
		prop_append(gbpsy, POWER_SUPPLY_PROP_MODEL_NAME);
	if (strlen(gbpsy->serial_number))
		prop_append(gbpsy, POWER_SUPPLY_PROP_SERIAL_NUMBER);
}
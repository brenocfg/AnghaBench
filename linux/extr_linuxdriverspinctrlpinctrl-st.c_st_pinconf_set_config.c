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
struct st_pio_control {struct regmap_field* od; struct regmap_field* pu; struct regmap_field* oe; } ;
struct regmap_field {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 unsigned long ST_PINCONF_OD ; 
 unsigned long ST_PINCONF_OE ; 
 unsigned long ST_PINCONF_PU ; 
 int /*<<< orphan*/  regmap_field_read (struct regmap_field*,unsigned int*) ; 
 int /*<<< orphan*/  regmap_field_write (struct regmap_field*,unsigned int) ; 

__attribute__((used)) static void st_pinconf_set_config(struct st_pio_control *pc,
				int pin, unsigned long config)
{
	struct regmap_field *output_enable = pc->oe;
	struct regmap_field *pull_up = pc->pu;
	struct regmap_field *open_drain = pc->od;
	unsigned int oe_value, pu_value, od_value;
	unsigned long mask = BIT(pin);

	if (output_enable) {
		regmap_field_read(output_enable, &oe_value);
		oe_value &= ~mask;
		if (config & ST_PINCONF_OE)
			oe_value |= mask;
		regmap_field_write(output_enable, oe_value);
	}

	if (pull_up) {
		regmap_field_read(pull_up, &pu_value);
		pu_value &= ~mask;
		if (config & ST_PINCONF_PU)
			pu_value |= mask;
		regmap_field_write(pull_up, pu_value);
	}

	if (open_drain) {
		regmap_field_read(open_drain, &od_value);
		od_value &= ~mask;
		if (config & ST_PINCONF_OD)
			od_value |= mask;
		regmap_field_write(open_drain, od_value);
	}
}
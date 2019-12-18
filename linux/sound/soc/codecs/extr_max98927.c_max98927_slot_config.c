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
struct max98927_priv {int v_l_slot; int i_l_slot; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 

__attribute__((used)) static void max98927_slot_config(struct i2c_client *i2c,
	struct max98927_priv *max98927)
{
	int value;
	struct device *dev = &i2c->dev;

	if (!device_property_read_u32(dev, "vmon-slot-no", &value))
		max98927->v_l_slot = value & 0xF;
	else
		max98927->v_l_slot = 0;

	if (!device_property_read_u32(dev, "imon-slot-no", &value))
		max98927->i_l_slot = value & 0xF;
	else
		max98927->i_l_slot = 1;
}
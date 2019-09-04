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
struct regmap_config {int val_bits; int reg_bits; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum ad193x_type { ____Placeholder_ad193x_type } ad193x_type ;

/* Variables and functions */
 int ad193x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct regmap_config ad193x_regmap_config ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 

__attribute__((used)) static int ad193x_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct regmap_config config;

	config = ad193x_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 8;

	return ad193x_probe(&client->dev,
			    devm_regmap_init_i2c(client, &config),
			    (enum ad193x_type)id->driver_data);
}
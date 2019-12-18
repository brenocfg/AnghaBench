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
struct regmap_config {int reg_bits; int val_bits; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int aic32x4_probe (int /*<<< orphan*/ *,struct regmap*) ; 
 struct regmap_config aic32x4_regmap_config ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 

__attribute__((used)) static int aic32x4_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;
	struct regmap_config config;

	config = aic32x4_regmap_config;
	config.reg_bits = 8;
	config.val_bits = 8;

	regmap = devm_regmap_init_i2c(i2c, &config);
	return aic32x4_probe(&i2c->dev, regmap);
}
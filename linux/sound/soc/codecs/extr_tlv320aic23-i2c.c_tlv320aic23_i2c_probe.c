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
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tlv320aic23_probe (int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  tlv320aic23_regmap ; 

__attribute__((used)) static int tlv320aic23_i2c_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *i2c_id)
{
	struct regmap *regmap;

	if (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EINVAL;

	regmap = devm_regmap_init_i2c(i2c, &tlv320aic23_regmap);
	return tlv320aic23_probe(&i2c->dev, regmap);
}
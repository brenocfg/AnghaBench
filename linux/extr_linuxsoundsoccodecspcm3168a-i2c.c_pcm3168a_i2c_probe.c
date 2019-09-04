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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int pcm3168a_probe (int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  pcm3168a_regmap ; 

__attribute__((used)) static int pcm3168a_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &pcm3168a_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return pcm3168a_probe(&i2c->dev, regmap);
}
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
 int /*<<< orphan*/  ak4671_dai ; 
 int /*<<< orphan*/  ak4671_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_ak4671 ; 

__attribute__((used)) static int ak4671_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_i2c(client, &ak4671_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to create regmap: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&client->dev,
			&soc_component_dev_ak4671, &ak4671_dai, 1);
	return ret;
}
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
struct ssm4567 {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSM4567_REG_SOFT_RESET ; 
 struct ssm4567* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ssm4567*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssm4567_component_driver ; 
 int /*<<< orphan*/  ssm4567_dai ; 
 int /*<<< orphan*/  ssm4567_regmap_config ; 
 int ssm4567_set_power (struct ssm4567*,int) ; 

__attribute__((used)) static int ssm4567_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct ssm4567 *ssm4567;
	int ret;

	ssm4567 = devm_kzalloc(&i2c->dev, sizeof(*ssm4567), GFP_KERNEL);
	if (ssm4567 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, ssm4567);

	ssm4567->regmap = devm_regmap_init_i2c(i2c, &ssm4567_regmap_config);
	if (IS_ERR(ssm4567->regmap))
		return PTR_ERR(ssm4567->regmap);

	ret = regmap_write(ssm4567->regmap, SSM4567_REG_SOFT_RESET, 0x00);
	if (ret)
		return ret;

	ret = ssm4567_set_power(ssm4567, false);
	if (ret)
		return ret;

	return devm_snd_soc_register_component(&i2c->dev, &ssm4567_component_driver,
			&ssm4567_dai, 1);
}
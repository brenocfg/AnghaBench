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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cs4349_private {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4349_dai ; 
 int /*<<< orphan*/  cs4349_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct cs4349_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs4349_private*) ; 
 int /*<<< orphan*/  soc_component_dev_cs4349 ; 

__attribute__((used)) static int cs4349_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	struct cs4349_private *cs4349;
	int ret;

	cs4349 = devm_kzalloc(&client->dev, sizeof(*cs4349), GFP_KERNEL);
	if (!cs4349)
		return -ENOMEM;

	cs4349->regmap = devm_regmap_init_i2c(client, &cs4349_regmap);
	if (IS_ERR(cs4349->regmap)) {
		ret = PTR_ERR(cs4349->regmap);
		dev_err(&client->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	/* Reset the Device */
	cs4349->reset_gpio = devm_gpiod_get_optional(&client->dev,
		"reset", GPIOD_OUT_LOW);
	if (IS_ERR(cs4349->reset_gpio))
		return PTR_ERR(cs4349->reset_gpio);

	gpiod_set_value_cansleep(cs4349->reset_gpio, 1);

	i2c_set_clientdata(client, cs4349);

	return devm_snd_soc_register_component(&client->dev,
		&soc_component_dev_cs4349,
		&cs4349_dai, 1);
}
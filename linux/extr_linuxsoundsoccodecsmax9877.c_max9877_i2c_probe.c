#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max9877_component_driver ; 
 int /*<<< orphan*/  max9877_regmap ; 
 TYPE_1__* max9877_regs ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max9877_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;
	int i;

	regmap = devm_regmap_init_i2c(client, &max9877_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Ensure the device is in reset state */
	for (i = 0; i < ARRAY_SIZE(max9877_regs); i++)
		regmap_write(regmap, max9877_regs[i].reg, max9877_regs[i].def);

	return devm_snd_soc_register_component(&client->dev,
			&max9877_component_driver, NULL, 0);
}
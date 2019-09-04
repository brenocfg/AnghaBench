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
struct tfa9879_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct tfa9879_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tfa9879_priv*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfa9879_component ; 
 int /*<<< orphan*/  tfa9879_dai ; 
 int /*<<< orphan*/  tfa9879_regmap ; 
 TYPE_1__* tfa9879_regs ; 

__attribute__((used)) static int tfa9879_i2c_probe(struct i2c_client *i2c)
{
	struct tfa9879_priv *tfa9879;
	int i;

	tfa9879 = devm_kzalloc(&i2c->dev, sizeof(*tfa9879), GFP_KERNEL);
	if (!tfa9879)
		return -ENOMEM;

	i2c_set_clientdata(i2c, tfa9879);

	tfa9879->regmap = devm_regmap_init_i2c(i2c, &tfa9879_regmap);
	if (IS_ERR(tfa9879->regmap))
		return PTR_ERR(tfa9879->regmap);

	/* Ensure the device is in reset state */
	for (i = 0; i < ARRAY_SIZE(tfa9879_regs); i++)
		regmap_write(tfa9879->regmap,
			     tfa9879_regs[i].reg, tfa9879_regs[i].def);

	return devm_snd_soc_register_component(&i2c->dev, &tfa9879_component,
					       &tfa9879_dai, 1);
}
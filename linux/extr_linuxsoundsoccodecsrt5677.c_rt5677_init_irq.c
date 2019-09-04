#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  jd3_gpio; int /*<<< orphan*/  jd2_gpio; int /*<<< orphan*/  jd1_gpio; } ;
struct rt5677_priv {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct rt5677_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5677_irq_chip ; 

__attribute__((used)) static int rt5677_init_irq(struct i2c_client *i2c)
{
	int ret;
	struct rt5677_priv *rt5677 = i2c_get_clientdata(i2c);

	if (!rt5677->pdata.jd1_gpio &&
		!rt5677->pdata.jd2_gpio &&
		!rt5677->pdata.jd3_gpio)
		return 0;

	if (!i2c->irq) {
		dev_err(&i2c->dev, "No interrupt specified\n");
		return -EINVAL;
	}

	ret = regmap_add_irq_chip(rt5677->regmap, i2c->irq,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT, 0,
		&rt5677_irq_chip, &rt5677->irq_data);

	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to register IRQ chip: %d\n", ret);
		return ret;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int jd1_gpio; int jd2_gpio; int jd3_gpio; } ;
struct rt5677_priv {int /*<<< orphan*/  domain; int /*<<< orphan*/  regmap; TYPE_1__ pdata; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  RT5677_DIG_MISC ; 
 int /*<<< orphan*/  RT5677_GEN_CTRL1 ; 
 unsigned int RT5677_GPIO1_PIN_IRQ ; 
 unsigned int RT5677_GPIO1_PIN_MASK ; 
 int /*<<< orphan*/  RT5677_GPIO_CTRL1 ; 
 unsigned int RT5677_IRQ_DEBOUNCE_SEL_MASK ; 
 unsigned int RT5677_IRQ_DEBOUNCE_SEL_RC ; 
 int /*<<< orphan*/  RT5677_IRQ_NUM ; 
 int /*<<< orphan*/  RT5677_JD_CTRL1 ; 
 unsigned int RT5677_SEL_GPIO_JD1_MASK ; 
 unsigned int RT5677_SEL_GPIO_JD1_SFT ; 
 unsigned int RT5677_SEL_GPIO_JD2_MASK ; 
 unsigned int RT5677_SEL_GPIO_JD2_SFT ; 
 unsigned int RT5677_SEL_GPIO_JD3_MASK ; 
 unsigned int RT5677_SEL_GPIO_JD3_SFT ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct rt5677_priv*) ; 
 struct rt5677_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rt5677_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rt5677_domain_ops ; 
 int /*<<< orphan*/  rt5677_irq ; 

__attribute__((used)) static int rt5677_init_irq(struct i2c_client *i2c)
{
	int ret;
	struct rt5677_priv *rt5677 = i2c_get_clientdata(i2c);
	unsigned int jd_mask = 0, jd_val = 0;

	if (!rt5677->pdata.jd1_gpio &&
		!rt5677->pdata.jd2_gpio &&
		!rt5677->pdata.jd3_gpio)
		return 0;

	if (!i2c->irq) {
		dev_err(&i2c->dev, "No interrupt specified\n");
		return -EINVAL;
	}

	mutex_init(&rt5677->irq_lock);

	/*
	 * Select RC as the debounce clock so that GPIO works even when
	 * MCLK is gated which happens when there is no audio stream
	 * (SND_SOC_BIAS_OFF).
	 */
	regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC,
			RT5677_IRQ_DEBOUNCE_SEL_MASK,
			RT5677_IRQ_DEBOUNCE_SEL_RC);
	/* Enable auto power on RC when GPIO states are changed */
	regmap_update_bits(rt5677->regmap, RT5677_GEN_CTRL1, 0xff, 0xff);

	/* Select and enable jack detection sources per platform data */
	if (rt5677->pdata.jd1_gpio) {
		jd_mask	|= RT5677_SEL_GPIO_JD1_MASK;
		jd_val	|= rt5677->pdata.jd1_gpio << RT5677_SEL_GPIO_JD1_SFT;
	}
	if (rt5677->pdata.jd2_gpio) {
		jd_mask	|= RT5677_SEL_GPIO_JD2_MASK;
		jd_val	|= rt5677->pdata.jd2_gpio << RT5677_SEL_GPIO_JD2_SFT;
	}
	if (rt5677->pdata.jd3_gpio) {
		jd_mask	|= RT5677_SEL_GPIO_JD3_MASK;
		jd_val	|= rt5677->pdata.jd3_gpio << RT5677_SEL_GPIO_JD3_SFT;
	}
	regmap_update_bits(rt5677->regmap, RT5677_JD_CTRL1, jd_mask, jd_val);

	/* Set GPIO1 pin to be IRQ output */
	regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL1,
			RT5677_GPIO1_PIN_MASK, RT5677_GPIO1_PIN_IRQ);

	/* Ready to listen for interrupts */
	rt5677->domain = irq_domain_add_linear(i2c->dev.of_node,
			RT5677_IRQ_NUM, &rt5677_domain_ops, rt5677);
	if (!rt5677->domain) {
		dev_err(&i2c->dev, "Failed to create IRQ domain\n");
		return -ENOMEM;
	}

	ret = devm_request_threaded_irq(&i2c->dev, i2c->irq, NULL, rt5677_irq,
			IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			"rt5677", rt5677);
	if (ret)
		dev_err(&i2c->dev, "Failed to request IRQ: %d\n", ret);

	return ret;
}
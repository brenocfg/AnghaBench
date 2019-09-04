#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int irq_flags; scalar_t__ reset_active_high; scalar_t__ gpio_reset; } ;
struct wm0010_priv {int gpio_reset_value; int irq; scalar_t__ board_max_spi_speed; int /*<<< orphan*/ * dev; TYPE_2__ pdata; int /*<<< orphan*/  state; scalar_t__ gpio_reset; int /*<<< orphan*/  dbvdd; TYPE_1__* core_supplies; int /*<<< orphan*/  boot_completion; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  lock; } ;
struct spi_device {int irq; int /*<<< orphan*/  dev; scalar_t__ max_speed_hz; } ;
struct TYPE_6__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long GPIOF_OUT_INIT_HIGH ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM0010_POWER_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,scalar_t__,unsigned long,char*) ; 
 struct wm0010_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int irq_set_irq_wake (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm0010_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm0010 ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wm0010_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* wm0010_dai ; 
 int /*<<< orphan*/  wm0010_irq ; 

__attribute__((used)) static int wm0010_spi_probe(struct spi_device *spi)
{
	unsigned long gpio_flags;
	int ret;
	int trigger;
	int irq;
	struct wm0010_priv *wm0010;

	wm0010 = devm_kzalloc(&spi->dev, sizeof(*wm0010),
			      GFP_KERNEL);
	if (!wm0010)
		return -ENOMEM;

	mutex_init(&wm0010->lock);
	spin_lock_init(&wm0010->irq_lock);

	spi_set_drvdata(spi, wm0010);
	wm0010->dev = &spi->dev;

	if (dev_get_platdata(&spi->dev))
		memcpy(&wm0010->pdata, dev_get_platdata(&spi->dev),
		       sizeof(wm0010->pdata));

	init_completion(&wm0010->boot_completion);

	wm0010->core_supplies[0].supply = "AVDD";
	wm0010->core_supplies[1].supply = "DCVDD";
	ret = devm_regulator_bulk_get(wm0010->dev, ARRAY_SIZE(wm0010->core_supplies),
				      wm0010->core_supplies);
	if (ret != 0) {
		dev_err(wm0010->dev, "Failed to obtain core supplies: %d\n",
			ret);
		return ret;
	}

	wm0010->dbvdd = devm_regulator_get(wm0010->dev, "DBVDD");
	if (IS_ERR(wm0010->dbvdd)) {
		ret = PTR_ERR(wm0010->dbvdd);
		dev_err(wm0010->dev, "Failed to obtain DBVDD: %d\n", ret);
		return ret;
	}

	if (wm0010->pdata.gpio_reset) {
		wm0010->gpio_reset = wm0010->pdata.gpio_reset;

		if (wm0010->pdata.reset_active_high)
			wm0010->gpio_reset_value = 1;
		else
			wm0010->gpio_reset_value = 0;

		if (wm0010->gpio_reset_value)
			gpio_flags = GPIOF_OUT_INIT_HIGH;
		else
			gpio_flags = GPIOF_OUT_INIT_LOW;

		ret = devm_gpio_request_one(wm0010->dev, wm0010->gpio_reset,
					    gpio_flags, "wm0010 reset");
		if (ret < 0) {
			dev_err(wm0010->dev,
				"Failed to request GPIO for DSP reset: %d\n",
				ret);
			return ret;
		}
	} else {
		dev_err(wm0010->dev, "No reset GPIO configured\n");
		return -EINVAL;
	}

	wm0010->state = WM0010_POWER_OFF;

	irq = spi->irq;
	if (wm0010->pdata.irq_flags)
		trigger = wm0010->pdata.irq_flags;
	else
		trigger = IRQF_TRIGGER_FALLING;
	trigger |= IRQF_ONESHOT;

	ret = request_threaded_irq(irq, NULL, wm0010_irq, trigger,
				   "wm0010", wm0010);
	if (ret) {
		dev_err(wm0010->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		return ret;
	}
	wm0010->irq = irq;

	ret = irq_set_irq_wake(irq, 1);
	if (ret) {
		dev_err(wm0010->dev, "Failed to set IRQ %d as wake source: %d\n",
			irq, ret);
		return ret;
	}

	if (spi->max_speed_hz)
		wm0010->board_max_spi_speed = spi->max_speed_hz;
	else
		wm0010->board_max_spi_speed = 0;

	ret = devm_snd_soc_register_component(&spi->dev,
				     &soc_component_dev_wm0010, wm0010_dai,
				     ARRAY_SIZE(wm0010_dai));
	if (ret < 0)
		return ret;

	return 0;
}
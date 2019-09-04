#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wl1251_platform_data {int power_gpio; int /*<<< orphan*/  use_eeprom; } ;
struct wl1251 {int power_gpio; scalar_t__ irq; struct ieee80211_hw* vio; int /*<<< orphan*/  use_eeprom; int /*<<< orphan*/ * if_ops; struct spi_device* if_priv; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct spi_device {int bits_per_word; scalar_t__ irq; TYPE_1__ dev; } ;
struct ieee80211_hw {struct wl1251* priv; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 scalar_t__ IS_ERR (struct ieee80211_hw*) ; 
 int PTR_ERR (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,TYPE_1__*) ; 
 struct wl1251_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int devm_gpio_request_one (TYPE_1__*,int,int /*<<< orphan*/ ,char*) ; 
 struct ieee80211_hw* devm_regulator_get (TYPE_1__*,char*) ; 
 int devm_request_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl1251*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  irq_set_irq_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (scalar_t__,int /*<<< orphan*/ ) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  regulator_disable (struct ieee80211_hw*) ; 
 int regulator_enable (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wl1251*) ; 
 int spi_setup (struct spi_device*) ; 
 struct ieee80211_hw* wl1251_alloc_hw () ; 
 int /*<<< orphan*/  wl1251_error (char*,...) ; 
 int wl1251_init_ieee80211 (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_irq ; 
 int /*<<< orphan*/  wl1251_spi_ops ; 

__attribute__((used)) static int wl1251_spi_probe(struct spi_device *spi)
{
	struct wl1251_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct device_node *np = spi->dev.of_node;
	struct ieee80211_hw *hw;
	struct wl1251 *wl;
	int ret;

	if (!np && !pdata) {
		wl1251_error("no platform data");
		return -ENODEV;
	}

	hw = wl1251_alloc_hw();
	if (IS_ERR(hw))
		return PTR_ERR(hw);

	wl = hw->priv;

	SET_IEEE80211_DEV(hw, &spi->dev);
	spi_set_drvdata(spi, wl);
	wl->if_priv = spi;
	wl->if_ops = &wl1251_spi_ops;

	/* This is the only SPI value that we need to set here, the rest
	 * comes from the board-peripherals file
	 */
	spi->bits_per_word = 32;

	ret = spi_setup(spi);
	if (ret < 0) {
		wl1251_error("spi_setup failed");
		goto out_free;
	}

	if (np) {
		wl->use_eeprom = of_property_read_bool(np, "ti,wl1251-has-eeprom");
		wl->power_gpio = of_get_named_gpio(np, "ti,power-gpio", 0);
	} else if (pdata) {
		wl->power_gpio = pdata->power_gpio;
		wl->use_eeprom = pdata->use_eeprom;
	}

	if (wl->power_gpio == -EPROBE_DEFER) {
		ret = -EPROBE_DEFER;
		goto out_free;
	}

	if (gpio_is_valid(wl->power_gpio)) {
		ret = devm_gpio_request_one(&spi->dev, wl->power_gpio,
					GPIOF_OUT_INIT_LOW, "wl1251 power");
		if (ret) {
			wl1251_error("Failed to request gpio: %d\n", ret);
			goto out_free;
		}
	} else {
		wl1251_error("set power gpio missing in platform data");
		ret = -ENODEV;
		goto out_free;
	}

	wl->irq = spi->irq;
	if (wl->irq < 0) {
		wl1251_error("irq missing in platform data");
		ret = -ENODEV;
		goto out_free;
	}

	irq_set_status_flags(wl->irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&spi->dev, wl->irq, wl1251_irq, 0,
							DRIVER_NAME, wl);
	if (ret < 0) {
		wl1251_error("request_irq() failed: %d", ret);
		goto out_free;
	}

	irq_set_irq_type(wl->irq, IRQ_TYPE_EDGE_RISING);

	wl->vio = devm_regulator_get(&spi->dev, "vio");
	if (IS_ERR(wl->vio)) {
		ret = PTR_ERR(wl->vio);
		wl1251_error("vio regulator missing: %d", ret);
		goto out_free;
	}

	ret = regulator_enable(wl->vio);
	if (ret)
		goto out_free;

	ret = wl1251_init_ieee80211(wl);
	if (ret)
		goto disable_regulator;

	return 0;

disable_regulator:
	regulator_disable(wl->vio);
out_free:
	ieee80211_free_hw(hw);

	return ret;
}
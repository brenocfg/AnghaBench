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
struct wl1251_sdio {struct sdio_func* func; } ;
struct wl1251_platform_data {int /*<<< orphan*/  use_eeprom; scalar_t__ irq; int /*<<< orphan*/  power_gpio; struct wl1251* priv; } ;
struct wl1251 {scalar_t__ irq; int /*<<< orphan*/  power_gpio; int /*<<< orphan*/  use_eeprom; TYPE_1__* if_ops; struct wl1251_sdio* if_priv; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_device_id {int dummy; } ;
typedef  struct ieee80211_hw {int /*<<< orphan*/  use_eeprom; scalar_t__ irq; int /*<<< orphan*/  power_gpio; struct wl1251* priv; } const ieee80211_hw ;
struct TYPE_2__ {int /*<<< orphan*/  disable_irq; int /*<<< orphan*/  enable_irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 scalar_t__ IS_ERR (struct wl1251_platform_data const*) ; 
 int PTR_ERR (struct wl1251_platform_data const*) ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct wl1251_platform_data const*,int /*<<< orphan*/ *) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct wl1251*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1251_sdio*) ; 
 struct wl1251_sdio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wl1251*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_block_size (struct sdio_func*,int) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct wl1251*) ; 
 struct wl1251_platform_data* wl1251_alloc_hw () ; 
 int /*<<< orphan*/  wl1251_disable_line_irq ; 
 int /*<<< orphan*/  wl1251_enable_line_irq ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 
 int /*<<< orphan*/  wl1251_free_hw (struct wl1251*) ; 
 struct wl1251_platform_data* wl1251_get_platform_data () ; 
 int /*<<< orphan*/  wl1251_info (char*) ; 
 int wl1251_init_ieee80211 (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_line_irq ; 
 int /*<<< orphan*/  wl1251_sdio_disable_irq ; 
 int /*<<< orphan*/  wl1251_sdio_enable_irq ; 
 TYPE_1__ wl1251_sdio_ops ; 

__attribute__((used)) static int wl1251_sdio_probe(struct sdio_func *func,
			     const struct sdio_device_id *id)
{
	int ret;
	struct wl1251 *wl;
	struct ieee80211_hw *hw;
	struct wl1251_sdio *wl_sdio;
	const struct wl1251_platform_data *wl1251_board_data;

	hw = wl1251_alloc_hw();
	if (IS_ERR(hw))
		return PTR_ERR(hw);

	wl = hw->priv;

	wl_sdio = kzalloc(sizeof(*wl_sdio), GFP_KERNEL);
	if (wl_sdio == NULL) {
		ret = -ENOMEM;
		goto out_free_hw;
	}

	sdio_claim_host(func);
	ret = sdio_enable_func(func);
	if (ret)
		goto release;

	sdio_set_block_size(func, 512);
	sdio_release_host(func);

	SET_IEEE80211_DEV(hw, &func->dev);
	wl_sdio->func = func;
	wl->if_priv = wl_sdio;
	wl->if_ops = &wl1251_sdio_ops;

	wl1251_board_data = wl1251_get_platform_data();
	if (!IS_ERR(wl1251_board_data)) {
		wl->power_gpio = wl1251_board_data->power_gpio;
		wl->irq = wl1251_board_data->irq;
		wl->use_eeprom = wl1251_board_data->use_eeprom;
	}

	if (gpio_is_valid(wl->power_gpio)) {
		ret = devm_gpio_request(&func->dev, wl->power_gpio,
								"wl1251 power");
		if (ret) {
			wl1251_error("Failed to request gpio: %d\n", ret);
			goto disable;
		}
	}

	if (wl->irq) {
		irq_set_status_flags(wl->irq, IRQ_NOAUTOEN);
		ret = request_irq(wl->irq, wl1251_line_irq, 0, "wl1251", wl);
		if (ret < 0) {
			wl1251_error("request_irq() failed: %d", ret);
			goto disable;
		}

		irq_set_irq_type(wl->irq, IRQ_TYPE_EDGE_RISING);

		wl1251_sdio_ops.enable_irq = wl1251_enable_line_irq;
		wl1251_sdio_ops.disable_irq = wl1251_disable_line_irq;

		wl1251_info("using dedicated interrupt line");
	} else {
		wl1251_sdio_ops.enable_irq = wl1251_sdio_enable_irq;
		wl1251_sdio_ops.disable_irq = wl1251_sdio_disable_irq;

		wl1251_info("using SDIO interrupt");
	}

	ret = wl1251_init_ieee80211(wl);
	if (ret)
		goto out_free_irq;

	sdio_set_drvdata(func, wl);

	/* Tell PM core that we don't need the card to be powered now */
	pm_runtime_put_noidle(&func->dev);

	return ret;

out_free_irq:
	if (wl->irq)
		free_irq(wl->irq, wl);
disable:
	sdio_claim_host(func);
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	kfree(wl_sdio);
out_free_hw:
	wl1251_free_hw(wl);
	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ar8xxx_priv {int chip_rev; int /*<<< orphan*/  get_port_link; struct ar8327_data* chip_data; } ;
struct ar8327_platform_data {int num_leds; int /*<<< orphan*/ * leds; TYPE_1__* sgmii_cfg; struct ar8327_led_cfg* led_cfg; TYPE_2__* pad6_cfg; TYPE_2__* pad5_cfg; TYPE_2__* pad0_cfg; int /*<<< orphan*/  port6_cfg; int /*<<< orphan*/  port0_cfg; int /*<<< orphan*/  get_port_link; } ;
struct ar8327_led_cfg {int led_ctrl0; int led_ctrl1; int led_ctrl2; int led_ctrl3; scalar_t__ open_drain; } ;
struct ar8327_data {int /*<<< orphan*/  leds; void* port6_status; void* port0_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac06_exchange_dis; } ;
struct TYPE_3__ {int sgmii_ctrl; scalar_t__ serdes_aen; } ;

/* Variables and functions */
 int AR8327_POWER_ON_STRIP_LED_OPEN_EN ; 
 int AR8327_POWER_ON_STRIP_POWER_ON_SEL ; 
 int AR8327_POWER_ON_STRIP_SERDES_AEN ; 
 int /*<<< orphan*/  AR8327_REG_LED_CTRL0 ; 
 int /*<<< orphan*/  AR8327_REG_LED_CTRL1 ; 
 int /*<<< orphan*/  AR8327_REG_LED_CTRL2 ; 
 int /*<<< orphan*/  AR8327_REG_LED_CTRL3 ; 
 int /*<<< orphan*/  AR8327_REG_PAD0_MODE ; 
 int /*<<< orphan*/  AR8327_REG_PAD5_MODE ; 
 int /*<<< orphan*/  AR8327_REG_PAD6_MODE ; 
 int /*<<< orphan*/  AR8327_REG_POWER_ON_STRIP ; 
 int /*<<< orphan*/  AR8327_REG_SGMII_CTRL ; 
 int AR8327_SGMII_CTRL_EN_PLL ; 
 int AR8327_SGMII_CTRL_EN_RX ; 
 int AR8327_SGMII_CTRL_EN_TX ; 
 int AR8337_PAD_MAC06_EXCHANGE_EN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ar8327_get_pad_cfg (TYPE_2__*) ; 
 void* ar8327_get_port_init_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar8327_led_create (struct ar8xxx_priv*,int /*<<< orphan*/ *) ; 
 int ar8xxx_read (struct ar8xxx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chip_is_ar8337 (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8327_hw_config_pdata(struct ar8xxx_priv *priv,
		       struct ar8327_platform_data *pdata)
{
	struct ar8327_led_cfg *led_cfg;
	struct ar8327_data *data = priv->chip_data;
	u32 pos, new_pos;
	u32 t;

	if (!pdata)
		return -EINVAL;

	priv->get_port_link = pdata->get_port_link;

	data->port0_status = ar8327_get_port_init_status(&pdata->port0_cfg);
	data->port6_status = ar8327_get_port_init_status(&pdata->port6_cfg);

	t = ar8327_get_pad_cfg(pdata->pad0_cfg);
	if (chip_is_ar8337(priv) && !pdata->pad0_cfg->mac06_exchange_dis)
	    t |= AR8337_PAD_MAC06_EXCHANGE_EN;
	ar8xxx_write(priv, AR8327_REG_PAD0_MODE, t);

	t = ar8327_get_pad_cfg(pdata->pad5_cfg);
	ar8xxx_write(priv, AR8327_REG_PAD5_MODE, t);
	t = ar8327_get_pad_cfg(pdata->pad6_cfg);
	ar8xxx_write(priv, AR8327_REG_PAD6_MODE, t);

	pos = ar8xxx_read(priv, AR8327_REG_POWER_ON_STRIP);
	new_pos = pos;

	led_cfg = pdata->led_cfg;
	if (led_cfg) {
		if (led_cfg->open_drain)
			new_pos |= AR8327_POWER_ON_STRIP_LED_OPEN_EN;
		else
			new_pos &= ~AR8327_POWER_ON_STRIP_LED_OPEN_EN;

		ar8xxx_write(priv, AR8327_REG_LED_CTRL0, led_cfg->led_ctrl0);
		ar8xxx_write(priv, AR8327_REG_LED_CTRL1, led_cfg->led_ctrl1);
		ar8xxx_write(priv, AR8327_REG_LED_CTRL2, led_cfg->led_ctrl2);
		ar8xxx_write(priv, AR8327_REG_LED_CTRL3, led_cfg->led_ctrl3);

		if (new_pos != pos)
			new_pos |= AR8327_POWER_ON_STRIP_POWER_ON_SEL;
	}

	if (pdata->sgmii_cfg) {
		t = pdata->sgmii_cfg->sgmii_ctrl;
		if (priv->chip_rev == 1)
			t |= AR8327_SGMII_CTRL_EN_PLL |
			     AR8327_SGMII_CTRL_EN_RX |
			     AR8327_SGMII_CTRL_EN_TX;
		else
			t &= ~(AR8327_SGMII_CTRL_EN_PLL |
			       AR8327_SGMII_CTRL_EN_RX |
			       AR8327_SGMII_CTRL_EN_TX);

		ar8xxx_write(priv, AR8327_REG_SGMII_CTRL, t);

		if (pdata->sgmii_cfg->serdes_aen)
			new_pos &= ~AR8327_POWER_ON_STRIP_SERDES_AEN;
		else
			new_pos |= AR8327_POWER_ON_STRIP_SERDES_AEN;
	}

	ar8xxx_write(priv, AR8327_REG_POWER_ON_STRIP, new_pos);

	if (pdata->leds && pdata->num_leds) {
		int i;

		data->leds = kzalloc(pdata->num_leds * sizeof(void *),
				     GFP_KERNEL);
		if (!data->leds)
			return -ENOMEM;

		for (i = 0; i < pdata->num_leds; i++)
			ar8327_led_create(priv, &pdata->leds[i]);
	}

	return 0;
}
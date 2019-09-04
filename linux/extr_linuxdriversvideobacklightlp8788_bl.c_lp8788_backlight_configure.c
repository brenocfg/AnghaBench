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
typedef  int u8 ;
struct lp8788_bl_config {int bl_mode; int dim_mode; int full_scale; int rise_time; int fall_time; int pwm_pol; } ;
struct lp8788_bl {int mode; TYPE_1__* lp; struct lp8788_backlight_platform_data* pdata; } ;
struct lp8788_backlight_platform_data {int bl_mode; int dim_mode; int full_scale; int rise_time; int fall_time; int pwm_pol; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LP8788_BL_COMB_PWM_BASED 130 
#define  LP8788_BL_COMB_REGISTER_BASED 129 
 int /*<<< orphan*/  LP8788_BL_CONFIG ; 
 int LP8788_BL_DIM_MODE_SHIFT ; 
 int LP8788_BL_EN ; 
 int LP8788_BL_FULLSCALE_SHIFT ; 
 int LP8788_BL_PWM_INPUT_EN ; 
 int LP8788_BL_PWM_POLARITY_SHIFT ; 
 int /*<<< orphan*/  LP8788_BL_RAMP ; 
 int LP8788_BL_RAMP_RISE_SHIFT ; 
#define  LP8788_BL_REGISTER_ONLY 128 
 struct lp8788_bl_config default_bl_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int lp8788_write_byte (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lp8788_backlight_configure(struct lp8788_bl *bl)
{
	struct lp8788_backlight_platform_data *pdata = bl->pdata;
	struct lp8788_bl_config *cfg = &default_bl_config;
	int ret;
	u8 val;

	/*
	 * Update chip configuration if platform data exists,
	 * otherwise use the default settings.
	 */
	if (pdata) {
		cfg->bl_mode    = pdata->bl_mode;
		cfg->dim_mode   = pdata->dim_mode;
		cfg->full_scale = pdata->full_scale;
		cfg->rise_time  = pdata->rise_time;
		cfg->fall_time  = pdata->fall_time;
		cfg->pwm_pol    = pdata->pwm_pol;
	}

	/* Brightness ramp up/down */
	val = (cfg->rise_time << LP8788_BL_RAMP_RISE_SHIFT) | cfg->fall_time;
	ret = lp8788_write_byte(bl->lp, LP8788_BL_RAMP, val);
	if (ret)
		return ret;

	/* Fullscale current setting */
	val = (cfg->full_scale << LP8788_BL_FULLSCALE_SHIFT) |
		(cfg->dim_mode << LP8788_BL_DIM_MODE_SHIFT);

	/* Brightness control mode */
	switch (cfg->bl_mode) {
	case LP8788_BL_REGISTER_ONLY:
		val |= LP8788_BL_EN;
		break;
	case LP8788_BL_COMB_PWM_BASED:
	case LP8788_BL_COMB_REGISTER_BASED:
		val |= LP8788_BL_EN | LP8788_BL_PWM_INPUT_EN |
			(cfg->pwm_pol << LP8788_BL_PWM_POLARITY_SHIFT);
		break;
	default:
		dev_err(bl->lp->dev, "invalid mode: %d\n", cfg->bl_mode);
		return -EINVAL;
	}

	bl->mode = cfg->bl_mode;

	return lp8788_write_byte(bl->lp, LP8788_BL_CONFIG, val);
}
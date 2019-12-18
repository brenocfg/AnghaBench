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
typedef  int u8 ;
typedef  int u16 ;
struct wm_hubs_dcs_cache {int dcs_cfg; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct wm_hubs_data {int dcs_readback_mode; scalar_t__ dcs_codes_l; scalar_t__ dcs_codes_r; scalar_t__ series_startup; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int WM8993_DCS_DAC_WR_VAL_1_SHIFT ; 
 int /*<<< orphan*/  WM8993_DCS_SERIES_NO_01_MASK ; 
 int WM8993_DCS_SERIES_NO_01_SHIFT ; 
 int WM8993_DCS_TRIG_DAC_WR_0 ; 
 int WM8993_DCS_TRIG_DAC_WR_1 ; 
 int WM8993_DCS_TRIG_SERIES_0 ; 
 int WM8993_DCS_TRIG_SERIES_1 ; 
 int WM8993_DCS_TRIG_STARTUP_0 ; 
 int WM8993_DCS_TRIG_STARTUP_1 ; 
 int /*<<< orphan*/  WM8993_DC_SERVO_1 ; 
 int WM8993_DC_SERVO_3 ; 
 int WM8994_DC_SERVO_4E ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int,int) ; 
 int /*<<< orphan*/  wait_for_dc_servo (struct snd_soc_component*,int) ; 
 scalar_t__ wm_hubs_dac_hp_direct (struct snd_soc_component*) ; 
 scalar_t__ wm_hubs_dcs_cache_get (struct snd_soc_component*,struct wm_hubs_dcs_cache**) ; 
 int /*<<< orphan*/  wm_hubs_dcs_cache_set (struct snd_soc_component*,int) ; 
 scalar_t__ wm_hubs_read_dc_servo (struct snd_soc_component*,int*,int*) ; 

__attribute__((used)) static void enable_dc_servo(struct snd_soc_component *component)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	struct wm_hubs_dcs_cache *cache;
	s8 offset;
	u16 reg_l, reg_r, dcs_cfg, dcs_reg;

	switch (hubs->dcs_readback_mode) {
	case 2:
		dcs_reg = WM8994_DC_SERVO_4E;
		break;
	default:
		dcs_reg = WM8993_DC_SERVO_3;
		break;
	}

	/* If we're using a digital only path and have a previously
	 * callibrated DC servo offset stored then use that. */
	if (wm_hubs_dac_hp_direct(component) &&
	    wm_hubs_dcs_cache_get(component, &cache)) {
		dev_dbg(component->dev, "Using cached DCS offset %x for %d,%d\n",
			cache->dcs_cfg, cache->left, cache->right);
		snd_soc_component_write(component, dcs_reg, cache->dcs_cfg);
		wait_for_dc_servo(component,
				  WM8993_DCS_TRIG_DAC_WR_0 |
				  WM8993_DCS_TRIG_DAC_WR_1);
		return;
	}

	if (hubs->series_startup) {
		/* Set for 32 series updates */
		snd_soc_component_update_bits(component, WM8993_DC_SERVO_1,
				    WM8993_DCS_SERIES_NO_01_MASK,
				    32 << WM8993_DCS_SERIES_NO_01_SHIFT);
		wait_for_dc_servo(component,
				  WM8993_DCS_TRIG_SERIES_0 |
				  WM8993_DCS_TRIG_SERIES_1);
	} else {
		wait_for_dc_servo(component,
				  WM8993_DCS_TRIG_STARTUP_0 |
				  WM8993_DCS_TRIG_STARTUP_1);
	}

	if (wm_hubs_read_dc_servo(component, &reg_l, &reg_r) < 0)
		return;

	dev_dbg(component->dev, "DCS input: %x %x\n", reg_l, reg_r);

	/* Apply correction to DC servo result */
	if (hubs->dcs_codes_l || hubs->dcs_codes_r) {
		dev_dbg(component->dev,
			"Applying %d/%d code DC servo correction\n",
			hubs->dcs_codes_l, hubs->dcs_codes_r);

		/* HPOUT1R */
		offset = (s8)reg_r;
		dev_dbg(component->dev, "DCS right %d->%d\n", offset,
			offset + hubs->dcs_codes_r);
		offset += hubs->dcs_codes_r;
		dcs_cfg = (u8)offset << WM8993_DCS_DAC_WR_VAL_1_SHIFT;

		/* HPOUT1L */
		offset = (s8)reg_l;
		dev_dbg(component->dev, "DCS left %d->%d\n", offset,
			offset + hubs->dcs_codes_l);
		offset += hubs->dcs_codes_l;
		dcs_cfg |= (u8)offset;

		dev_dbg(component->dev, "DCS result: %x\n", dcs_cfg);

		/* Do it */
		snd_soc_component_write(component, dcs_reg, dcs_cfg);
		wait_for_dc_servo(component,
				  WM8993_DCS_TRIG_DAC_WR_0 |
				  WM8993_DCS_TRIG_DAC_WR_1);
	} else {
		dcs_cfg = reg_r << WM8993_DCS_DAC_WR_VAL_1_SHIFT;
		dcs_cfg |= reg_l;
	}

	/* Save the callibrated offset if we're in class W mode and
	 * therefore don't have any analogue signal mixed in. */
	if (wm_hubs_dac_hp_direct(component))
		wm_hubs_dcs_cache_set(component, dcs_cfg);
}
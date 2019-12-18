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
struct wm8770_priv {int /*<<< orphan*/  supplies; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8770_DAC1RVOL ; 
 int /*<<< orphan*/  WM8770_DAC2RVOL ; 
 int /*<<< orphan*/  WM8770_DAC3RVOL ; 
 int /*<<< orphan*/  WM8770_DAC4RVOL ; 
 int /*<<< orphan*/  WM8770_DACMUTE ; 
 int /*<<< orphan*/  WM8770_MSALGVOL ; 
 int /*<<< orphan*/  WM8770_MSDIGVOL ; 
 int /*<<< orphan*/  WM8770_VOUT1RVOL ; 
 int /*<<< orphan*/  WM8770_VOUT2RVOL ; 
 int /*<<< orphan*/  WM8770_VOUT3RVOL ; 
 int /*<<< orphan*/  WM8770_VOUT4RVOL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm8770_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8770_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8770_probe(struct snd_soc_component *component)
{
	struct wm8770_priv *wm8770;
	int ret;

	wm8770 = snd_soc_component_get_drvdata(component);
	wm8770->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8770->supplies),
				    wm8770->supplies);
	if (ret) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = wm8770_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		goto err_reg_enable;
	}

	/* latch the volume update bits */
	snd_soc_component_update_bits(component, WM8770_MSDIGVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_MSALGVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT1RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT2RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT3RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_VOUT4RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC1RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC2RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC3RVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8770_DAC4RVOL, 0x100, 0x100);

	/* mute all DACs */
	snd_soc_component_update_bits(component, WM8770_DACMUTE, 0x10, 0x10);

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8770->supplies), wm8770->supplies);
	return ret;
}
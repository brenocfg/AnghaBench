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
typedef  int u16 ;
struct wm8940_setup_data {int vroi; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct TYPE_3__ {struct wm8940_setup_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM8940_OUTPUTCTL ; 
 int /*<<< orphan*/  WM8940_POWER1 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int wm8940_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8940_probe(struct snd_soc_component *component)
{
	struct wm8940_setup_data *pdata = component->dev->platform_data;
	int ret;
	u16 reg;

	ret = wm8940_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset\n");
		return ret;
	}

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	ret = snd_soc_component_write(component, WM8940_POWER1, 0x180);
	if (ret < 0)
		return ret;

	if (!pdata)
		dev_warn(component->dev, "No platform data supplied\n");
	else {
		reg = snd_soc_component_read32(component, WM8940_OUTPUTCTL);
		ret = snd_soc_component_write(component, WM8940_OUTPUTCTL, reg | pdata->vroi);
		if (ret < 0)
			return ret;
	}

	return ret;
}
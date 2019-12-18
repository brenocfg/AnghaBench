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
typedef  int u16 ;
struct wm8711_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8711_ACTIVE ; 
 int /*<<< orphan*/  WM8711_PWR ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8711_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8711_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct wm8711_priv *wm8711 = snd_soc_component_get_drvdata(component);
	u16 reg = snd_soc_component_read32(component, WM8711_PWR) & 0xff7f;

	switch (level) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_write(component, WM8711_PWR, reg);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(wm8711->regmap);

		snd_soc_component_write(component, WM8711_PWR, reg | 0x0040);
		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, WM8711_ACTIVE, 0x0);
		snd_soc_component_write(component, WM8711_PWR, 0xffff);
		break;
	}
	return 0;
}
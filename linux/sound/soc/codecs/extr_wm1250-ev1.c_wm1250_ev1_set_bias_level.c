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
struct wm1250_priv {TYPE_1__* gpios; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {int gpio; } ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 size_t WM1250_EV1_GPIO_CLK_ENA ; 
 struct wm1250_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int,int) ; 

__attribute__((used)) static int wm1250_ev1_set_bias_level(struct snd_soc_component *component,
				     enum snd_soc_bias_level level)
{
	struct wm1250_priv *wm1250 = dev_get_drvdata(component->dev);
	int ena;

	if (wm1250)
		ena = wm1250->gpios[WM1250_EV1_GPIO_CLK_ENA].gpio;
	else
		ena = -1;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		if (ena >= 0)
			gpio_set_value_cansleep(ena, 1);
		break;

	case SND_SOC_BIAS_OFF:
		if (ena >= 0)
			gpio_set_value_cansleep(ena, 0);
		break;
	}

	return 0;
}
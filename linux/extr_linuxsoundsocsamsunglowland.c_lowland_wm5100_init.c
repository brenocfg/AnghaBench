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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKOUT_RATE ; 
 int /*<<< orphan*/  MCLK1_RATE ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM5100_CLKSRC_MCLK1 ; 
 int /*<<< orphan*/  WM5100_CLK_OPCLK ; 
 int /*<<< orphan*/  WM5100_CLK_SYSCLK ; 
 int /*<<< orphan*/  lowland_headset ; 
 int /*<<< orphan*/  lowland_headset_pins ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm5100_detect (struct snd_soc_component*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lowland_wm5100_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	int ret;

	ret = snd_soc_component_set_sysclk(component, WM5100_CLK_SYSCLK,
				       WM5100_CLKSRC_MCLK1, MCLK1_RATE,
				       SND_SOC_CLOCK_IN);
	if (ret < 0) {
		pr_err("Failed to set SYSCLK clock source: %d\n", ret);
		return ret;
	}

	/* Clock OPCLK, used by the other audio components. */
	ret = snd_soc_component_set_sysclk(component, WM5100_CLK_OPCLK, 0,
				       CLKOUT_RATE, 0);
	if (ret < 0) {
		pr_err("Failed to set OPCLK rate: %d\n", ret);
		return ret;
	}

	ret = snd_soc_card_jack_new(rtd->card, "Headset", SND_JACK_LINEOUT |
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &lowland_headset, lowland_headset_pins,
				    ARRAY_SIZE(lowland_headset_pins));
	if (ret)
		return ret;

	wm5100_detect(component, &lowland_headset);

	return 0;
}
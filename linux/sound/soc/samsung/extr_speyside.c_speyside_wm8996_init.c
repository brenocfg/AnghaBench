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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  WM8996_HPSEL_GPIO ; 
 int /*<<< orphan*/  WM8996_SYSCLK_MCLK2 ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speyside_headset ; 
 int /*<<< orphan*/  speyside_headset_pins ; 
 int /*<<< orphan*/  speyside_jack_polarity ; 
 int /*<<< orphan*/  speyside_set_polarity ; 
 int /*<<< orphan*/  wm8996_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speyside_wm8996_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *dai = rtd->codec_dai;
	struct snd_soc_component *component = dai->component;
	int ret;

	ret = snd_soc_dai_set_sysclk(dai, WM8996_SYSCLK_MCLK2, 32768, 0);
	if (ret < 0)
		return ret;

	ret = gpio_request(WM8996_HPSEL_GPIO, "HP_SEL");
	if (ret != 0)
		pr_err("Failed to request HP_SEL GPIO: %d\n", ret);
	gpio_direction_output(WM8996_HPSEL_GPIO, speyside_jack_polarity);

	ret = snd_soc_card_jack_new(rtd->card, "Headset", SND_JACK_LINEOUT |
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &speyside_headset, speyside_headset_pins,
				    ARRAY_SIZE(speyside_headset_pins));
	if (ret)
		return ret;

	wm8996_detect(component, &speyside_headset, speyside_set_polarity);

	return 0;
}
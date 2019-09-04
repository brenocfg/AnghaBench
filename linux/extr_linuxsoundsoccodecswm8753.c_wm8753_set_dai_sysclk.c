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
struct wm8753_priv {unsigned int sysclk; unsigned int pcmclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8753_MCLK ; 
 int WM8753_PCMCLK ; 
 struct wm8753_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8753_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	switch (freq) {
	case 11289600:
	case 12000000:
	case 12288000:
	case 16934400:
	case 18432000:
		if (clk_id == WM8753_MCLK) {
			wm8753->sysclk = freq;
			return 0;
		} else if (clk_id == WM8753_PCMCLK) {
			wm8753->pcmclk = freq;
			return 0;
		}
		break;
	}
	return -EINVAL;
}
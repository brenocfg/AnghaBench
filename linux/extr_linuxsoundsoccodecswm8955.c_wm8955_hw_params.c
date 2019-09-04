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
struct wm8955_priv {int /*<<< orphan*/  fs; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8955_AUDIO_INTERFACE ; 
 int /*<<< orphan*/  WM8955_CLOCKING_PLL ; 
 int WM8955_DIGENB ; 
 int WM8955_PLLEN ; 
 int WM8955_PLL_RB ; 
 int /*<<< orphan*/  WM8955_POWER_MANAGEMENT_1 ; 
 int WM8955_WL_MASK ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8955_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm8955_configure_clocking (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8955_set_deemph (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8955_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	int ret;
	int wl;

	switch (params_width(params)) {
	case 16:
		wl = 0;
		break;
	case 20:
		wl = 0x4;
		break;
	case 24:
		wl = 0x8;
		break;
	case 32:
		wl = 0xc;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, WM8955_AUDIO_INTERFACE,
			    WM8955_WL_MASK, wl);

	wm8955->fs = params_rate(params);
	wm8955_set_deemph(component);

	/* If the chip is clocked then disable the clocks and force a
	 * reconfiguration, otherwise DAPM will power up the
	 * clocks for us later. */
	ret = snd_soc_component_read32(component, WM8955_POWER_MANAGEMENT_1);
	if (ret < 0)
		return ret;
	if (ret & WM8955_DIGENB) {
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_DIGENB, 0);
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLL_RB | WM8955_PLLEN, 0);

		wm8955_configure_clocking(component);
	}

	return 0;
}
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
struct wm2200_priv {int symmetric_rates; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int WM2200_AIF1TX_LRCLK_SRC ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_2 ; 
 int WM2200_GP1_FN_MASK ; 
 int /*<<< orphan*/  WM2200_GPIO_CTRL_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm2200_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm2200_dai_probe(struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	unsigned int val = 0;
	int ret;

	ret = snd_soc_component_read32(component, WM2200_GPIO_CTRL_1);
	if (ret >= 0) {
		if ((ret & WM2200_GP1_FN_MASK) != 0) {
			wm2200->symmetric_rates = true;
			val = WM2200_AIF1TX_LRCLK_SRC;
		}
	} else {
		dev_err(component->dev, "Failed to read GPIO 1 config: %d\n", ret);
	}

	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_2,
			    WM2200_AIF1TX_LRCLK_SRC, val);

	return 0;
}
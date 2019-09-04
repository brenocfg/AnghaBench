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
struct wm8753_priv {int dai_func; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8753_DAC ; 
 struct wm8753_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_is_active (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8753_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_read32(component, WM8753_DAC) & 0xfff7;
	struct wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);

	/* the digital mute covers the HiFi and Voice DAC's on the WM8753.
	 * make sure we check if they are not both active when we mute */
	if (mute && wm8753->dai_func == 1) {
		if (!snd_soc_component_is_active(component))
			snd_soc_component_write(component, WM8753_DAC, mute_reg | 0x8);
	} else {
		if (mute)
			snd_soc_component_write(component, WM8753_DAC, mute_reg | 0x8);
		else
			snd_soc_component_write(component, WM8753_DAC, mute_reg);
	}

	return 0;
}
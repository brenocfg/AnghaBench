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
struct wm9081_priv {int tdm_width; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int WM9081_AIFDAC_TDM_MODE_MASK ; 
 int WM9081_AIFDAC_TDM_MODE_SHIFT ; 
 unsigned int WM9081_AIFDAC_TDM_SLOT_MASK ; 
 int /*<<< orphan*/  WM9081_AUDIO_INTERFACE_1 ; 
 struct wm9081_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm9081_set_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	unsigned int aif1 = snd_soc_component_read32(component, WM9081_AUDIO_INTERFACE_1);

	aif1 &= ~(WM9081_AIFDAC_TDM_SLOT_MASK | WM9081_AIFDAC_TDM_MODE_MASK);

	if (slots < 0 || slots > 4)
		return -EINVAL;

	wm9081->tdm_width = slot_width;

	if (slots == 0)
		slots = 1;

	aif1 |= (slots - 1) << WM9081_AIFDAC_TDM_MODE_SHIFT;

	switch (rx_mask) {
	case 1:
		break;
	case 2:
		aif1 |= 0x10;
		break;
	case 4:
		aif1 |= 0x20;
		break;
	case 8:
		aif1 |= 0x30;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, WM9081_AUDIO_INTERFACE_1, aif1);

	return 0;
}
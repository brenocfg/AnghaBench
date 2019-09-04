#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int id; TYPE_3__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct arizona_priv {struct arizona* arizona; } ;
struct arizona {int* tdm_width; int* tdm_slots; } ;
struct TYPE_5__ {int channels_max; } ;
struct TYPE_4__ {int channels_max; } ;
struct TYPE_6__ {int base; TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 scalar_t__ ARIZONA_AIF_FRAME_CTRL_11 ; 
 scalar_t__ ARIZONA_AIF_FRAME_CTRL_3 ; 
 int ARIZONA_MAX_AIF ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  arizona_set_channels_to_mask (struct snd_soc_dai*,scalar_t__,int,unsigned int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int arizona_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
				unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	int base = dai->driver->base;
	int rx_max_chan = dai->driver->playback.channels_max;
	int tx_max_chan = dai->driver->capture.channels_max;

	/* Only support TDM for the physical AIFs */
	if (dai->id > ARIZONA_MAX_AIF)
		return -ENOTSUPP;

	if (slots == 0) {
		tx_mask = (1 << tx_max_chan) - 1;
		rx_mask = (1 << rx_max_chan) - 1;
	}

	arizona_set_channels_to_mask(dai, base + ARIZONA_AIF_FRAME_CTRL_3,
				     tx_max_chan, tx_mask);
	arizona_set_channels_to_mask(dai, base + ARIZONA_AIF_FRAME_CTRL_11,
				     rx_max_chan, rx_mask);

	arizona->tdm_width[dai->id - 1] = slot_width;
	arizona->tdm_slots[dai->id - 1] = slots;

	return 0;
}
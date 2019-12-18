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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct hdac_hda_priv {struct hdac_hda_pcm* pcm; } ;
struct hdac_hda_pcm {unsigned int* stream_tag; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdac_hda_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int hdac_hda_dai_set_tdm_slot(struct snd_soc_dai *dai,
				     unsigned int tx_mask, unsigned int rx_mask,
				     int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct hdac_hda_priv *hda_pvt;
	struct hdac_hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = &hda_pvt->pcm[dai->id];
	if (tx_mask)
		pcm[dai->id].stream_tag[SNDRV_PCM_STREAM_PLAYBACK] = tx_mask;
	else
		pcm[dai->id].stream_tag[SNDRV_PCM_STREAM_CAPTURE] = rx_mask;

	return 0;
}
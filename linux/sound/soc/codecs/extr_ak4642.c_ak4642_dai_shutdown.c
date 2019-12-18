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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC ; 
 int /*<<< orphan*/  ALC_CTL1 ; 
 int /*<<< orphan*/  PMADL ; 
 int /*<<< orphan*/  PMADR ; 
 int /*<<< orphan*/  PW_MGMT1 ; 
 int /*<<< orphan*/  PW_MGMT3 ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ak4642_dai_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	int is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	struct snd_soc_component *component = dai->component;

	if (is_play) {
	} else {
		/* stop stereo input */
		snd_soc_component_update_bits(component, PW_MGMT1, PMADL, 0);
		snd_soc_component_update_bits(component, PW_MGMT3, PMADR, 0);
		snd_soc_component_update_bits(component, ALC_CTL1, ALC, 0);
	}
}
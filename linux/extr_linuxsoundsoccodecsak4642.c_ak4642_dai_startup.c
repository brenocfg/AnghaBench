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
 int ALC ; 
 int /*<<< orphan*/  ALC_CTL1 ; 
 int LMTH0 ; 
 int /*<<< orphan*/  L_IVC ; 
 int MGAIN0 ; 
 int PMADL ; 
 int PMADR ; 
 int PMMP ; 
 int /*<<< orphan*/  PW_MGMT1 ; 
 int /*<<< orphan*/  PW_MGMT3 ; 
 int /*<<< orphan*/  R_IVC ; 
 int /*<<< orphan*/  SG_SL1 ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TIMER ; 
 int WTM (int) ; 
 int ZTM (int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak4642_dai_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	int is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	struct snd_soc_component *component = dai->component;

	if (is_play) {
		/*
		 * start headphone output
		 *
		 * PLL, Master Mode
		 * Audio I/F Format :MSB justified (ADC & DAC)
		 * Bass Boost Level : Middle
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p97.
		 */
		snd_soc_component_write(component, L_IVC, 0x91); /* volume */
		snd_soc_component_write(component, R_IVC, 0x91); /* volume */
	} else {
		/*
		 * start stereo input
		 *
		 * PLL Master Mode
		 * Audio I/F Format:MSB justified (ADC & DAC)
		 * Pre MIC AMP:+20dB
		 * MIC Power On
		 * ALC setting:Refer to Table 35
		 * ALC bit=“1”
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p94.
		 */
		snd_soc_component_update_bits(component, SG_SL1, PMMP | MGAIN0, PMMP | MGAIN0);
		snd_soc_component_write(component, TIMER, ZTM(0x3) | WTM(0x3));
		snd_soc_component_write(component, ALC_CTL1, ALC | LMTH0);
		snd_soc_component_update_bits(component, PW_MGMT1, PMADL, PMADL);
		snd_soc_component_update_bits(component, PW_MGMT3, PMADR, PMADR);
	}

	return 0;
}
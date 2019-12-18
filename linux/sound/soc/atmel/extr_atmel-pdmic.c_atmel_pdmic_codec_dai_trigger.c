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
typedef  int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDMIC_CR ; 
 int PDMIC_CR_ENPDM_DIS ; 
 int PDMIC_CR_ENPDM_EN ; 
 int /*<<< orphan*/  PDMIC_CR_ENPDM_MASK ; 
 int PDMIC_CR_ENPDM_SHIFT ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_pdmic_codec_dai_trigger(struct snd_pcm_substream *substream,
					int cmd, struct snd_soc_dai *codec_dai)
{
	struct snd_soc_component *component = codec_dai->component;
	u32 val;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = PDMIC_CR_ENPDM_EN << PDMIC_CR_ENPDM_SHIFT;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = PDMIC_CR_ENPDM_DIS << PDMIC_CR_ENPDM_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, PDMIC_CR, PDMIC_CR_ENPDM_MASK, val);

	return 0;
}
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
struct snd_pcm_substream {int dummy; } ;
struct es1938 {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESS_CMD_DMACONTROL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_es1938_write (struct es1938*,int /*<<< orphan*/ ,int) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	int val;
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		val = 0x0f;
		chip->active |= ADC1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		val = 0x00;
		chip->active &= ~ADC1;
		break;
	default:
		return -EINVAL;
	}
	snd_es1938_write(chip, ESS_CMD_DMACONTROL, val);
	return 0;
}
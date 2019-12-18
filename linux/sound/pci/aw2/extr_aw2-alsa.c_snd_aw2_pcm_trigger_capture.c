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
struct aw2_pcm_device {int /*<<< orphan*/  stream_number; struct aw2* chip; } ;
struct aw2 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  saa7146; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  snd_aw2_saa7146_pcm_trigger_start_capture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_aw2_saa7146_pcm_trigger_stop_capture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct aw2_pcm_device* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_aw2_pcm_trigger_capture(struct snd_pcm_substream *substream,
				       int cmd)
{
	int status = 0;
	struct aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	struct aw2 *chip = pcm_device->chip;
	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_aw2_saa7146_pcm_trigger_start_capture(&chip->saa7146,
							  pcm_device->
							  stream_number);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		snd_aw2_saa7146_pcm_trigger_stop_capture(&chip->saa7146,
							 pcm_device->
							 stream_number);
		break;
	default:
		status = -EINVAL;
	}
	spin_unlock(&chip->reg_lock);
	return status;
}
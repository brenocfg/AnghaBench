#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm {int /*<<< orphan*/  device; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_PCM ; 
 int /*<<< orphan*/  pcm_err (struct snd_pcm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_oss_f_reg ; 
 scalar_t__ snd_register_oss_device (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct snd_pcm*) ; 

__attribute__((used)) static void register_oss_dsp(struct snd_pcm *pcm, int index)
{
	if (snd_register_oss_device(SNDRV_OSS_DEVICE_TYPE_PCM,
				    pcm->card, index, &snd_pcm_oss_f_reg,
				    pcm) < 0) {
		pcm_err(pcm, "unable to register OSS PCM device %i:%i\n",
			   pcm->card->number, pcm->device);
	}
}
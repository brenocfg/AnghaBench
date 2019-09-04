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
struct snd_wss {TYPE_1__* pcm; } ;
struct TYPE_2__ {int /*<<< orphan*/  info_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int snd_wss_pcm (struct snd_wss*,int) ; 

int snd_cs4236_pcm(struct snd_wss *chip, int device)
{
	int err;
	
	err = snd_wss_pcm(chip, device);
	if (err < 0)
		return err;
	chip->pcm->info_flags &= ~SNDRV_PCM_INFO_JOINT_DUPLEX;
	return 0;
}
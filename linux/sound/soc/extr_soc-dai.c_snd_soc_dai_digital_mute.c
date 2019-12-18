#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* mute_stream ) (struct snd_soc_dai*,int,int) ;int (* digital_mute ) (struct snd_soc_dai*,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int stub1 (struct snd_soc_dai*,int,int) ; 
 int stub2 (struct snd_soc_dai*,int) ; 

int snd_soc_dai_digital_mute(struct snd_soc_dai *dai, int mute,
			     int direction)
{
	if (dai->driver->ops->mute_stream)
		return dai->driver->ops->mute_stream(dai, mute, direction);
	else if (direction == SNDRV_PCM_STREAM_PLAYBACK &&
		 dai->driver->ops->digital_mute)
		return dai->driver->ops->digital_mute(dai, mute);
	else
		return -ENOTSUPP;
}
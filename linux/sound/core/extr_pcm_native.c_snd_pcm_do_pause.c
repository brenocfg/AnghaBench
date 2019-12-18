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
struct snd_pcm_substream {TYPE_2__* ops; TYPE_1__* runtime; } ;
struct TYPE_4__ {int (* trigger ) (struct snd_pcm_substream*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ hw_ptr_jiffies; struct snd_pcm_substream* trigger_master; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_PAUSE_PUSH ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_PAUSE_RELEASE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_do_pause(struct snd_pcm_substream *substream, int push)
{
	if (substream->runtime->trigger_master != substream)
		return 0;
	/* some drivers might use hw_ptr to recover from the pause -
	   update the hw_ptr now */
	if (push)
		snd_pcm_update_hw_ptr(substream);
	/* The jiffies check in snd_pcm_update_hw_ptr*() is done by
	 * a delta between the current jiffies, this gives a large enough
	 * delta, effectively to skip the check once.
	 */
	substream->runtime->hw_ptr_jiffies = jiffies - HZ * 1000;
	return substream->ops->trigger(substream,
				       push ? SNDRV_PCM_TRIGGER_PAUSE_PUSH :
					      SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
}
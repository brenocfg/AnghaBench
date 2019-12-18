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

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_RUNNING ; 
 int snd_pcm_action_lock_irq (int /*<<< orphan*/ *,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_action_start ; 

__attribute__((used)) static int snd_pcm_start_lock_irq(struct snd_pcm_substream *substream)
{
	return snd_pcm_action_lock_irq(&snd_pcm_action_start, substream,
				       SNDRV_PCM_STATE_RUNNING);
}
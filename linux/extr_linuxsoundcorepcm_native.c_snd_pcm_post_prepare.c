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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_2__* status; TYPE_1__* control; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  appl_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_PREPARED ; 
 int /*<<< orphan*/  snd_pcm_set_state (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_pcm_post_prepare(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	runtime->control->appl_ptr = runtime->status->hw_ptr;
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_PREPARED);
}
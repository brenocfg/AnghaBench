#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_usX2Y_substream {int /*<<< orphan*/  state; TYPE_2__* usX2Y; } ;
struct snd_pcm_substream {TYPE_3__* runtime; } ;
struct TYPE_6__ {struct snd_usX2Y_substream* private_data; } ;
struct TYPE_5__ {TYPE_1__** subs; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 
 int /*<<< orphan*/  state_PREPARED ; 
 int /*<<< orphan*/  state_PRERUNNING ; 

__attribute__((used)) static int snd_usX2Y_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_usX2Y_substream *subs = substream->runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_printdd("snd_usX2Y_pcm_trigger(START)\n");
		if (atomic_read(&subs->state) == state_PREPARED &&
		    atomic_read(&subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE]->state) >= state_PREPARED) {
			atomic_set(&subs->state, state_PRERUNNING);
		} else {
			snd_printdd("\n");
			return -EPIPE;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		snd_printdd("snd_usX2Y_pcm_trigger(STOP)\n");
		if (atomic_read(&subs->state) >= state_PRERUNNING)
			atomic_set(&subs->state, state_PREPARED);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
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
struct snd_compr_stream {TYPE_2__* runtime; TYPE_1__* ops; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  sleep; } ;
struct TYPE_3__ {int (* trigger ) (struct snd_compr_stream*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
 int EPIPE ; 
#define  SNDRV_PCM_STATE_OPEN 132 
#define  SNDRV_PCM_STATE_PAUSED 131 
#define  SNDRV_PCM_STATE_PREPARED 130 
#define  SNDRV_PCM_STATE_SETUP 129 
#define  SNDRV_PCM_STATE_XRUN 128 
 int /*<<< orphan*/  SND_COMPR_TRIGGER_DRAIN ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int snd_compress_wait_for_drain (struct snd_compr_stream*) ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_compr_drain(struct snd_compr_stream *stream)
{
	int retval;

	switch (stream->runtime->state) {
	case SNDRV_PCM_STATE_OPEN:
	case SNDRV_PCM_STATE_SETUP:
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_PAUSED:
		return -EPERM;
	case SNDRV_PCM_STATE_XRUN:
		return -EPIPE;
	default:
		break;
	}

	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_DRAIN);
	if (retval) {
		pr_debug("SND_COMPR_TRIGGER_DRAIN failed %d\n", retval);
		wake_up(&stream->runtime->sleep);
		return retval;
	}

	return snd_compress_wait_for_drain(stream);
}
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
struct snd_compr_stream {TYPE_2__* runtime; TYPE_1__* ops; int /*<<< orphan*/  direction; } ;
struct TYPE_4__ {int state; } ;
struct TYPE_3__ {int (* trigger ) (struct snd_compr_stream*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
#define  SNDRV_PCM_STATE_PREPARED 129 
 int SNDRV_PCM_STATE_RUNNING ; 
#define  SNDRV_PCM_STATE_SETUP 128 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_START ; 
 int /*<<< orphan*/  SND_COMPRESS_CAPTURE ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compr_start(struct snd_compr_stream *stream)
{
	int retval;

	switch (stream->runtime->state) {
	case SNDRV_PCM_STATE_SETUP:
		if (stream->direction != SND_COMPRESS_CAPTURE)
			return -EPERM;
		break;
	case SNDRV_PCM_STATE_PREPARED:
		break;
	default:
		return -EPERM;
	}

	retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_START);
	if (!retval)
		stream->runtime->state = SNDRV_PCM_STATE_RUNNING;
	return retval;
}
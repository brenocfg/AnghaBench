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
struct snd_compr_stream {scalar_t__ direction; int next_track; TYPE_2__* runtime; TYPE_1__* ops; } ;
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
 scalar_t__ SND_COMPRESS_CAPTURE ; 
 int /*<<< orphan*/  SND_COMPR_TRIGGER_PARTIAL_DRAIN ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int snd_compress_wait_for_drain (struct snd_compr_stream*) ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_compr_partial_drain(struct snd_compr_stream *stream)
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

	/* partial drain doesn't have any meaning for capture streams */
	if (stream->direction == SND_COMPRESS_CAPTURE)
		return -EPERM;

	/* stream can be drained only when next track has been signalled */
	if (stream->next_track == false)
		return -EPERM;

	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_PARTIAL_DRAIN);
	if (retval) {
		pr_debug("Partial drain returned failure\n");
		wake_up(&stream->runtime->sleep);
		return retval;
	}

	stream->next_track = false;
	return snd_compress_wait_for_drain(stream);
}
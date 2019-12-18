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
struct snd_compr_stream {scalar_t__ direction; int metadata_set; int next_track; TYPE_2__* ops; TYPE_1__* runtime; } ;
struct TYPE_4__ {int (* trigger ) (struct snd_compr_stream*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 scalar_t__ SND_COMPRESS_CAPTURE ; 
 int /*<<< orphan*/  SND_COMPR_TRIGGER_NEXT_TRACK ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compr_next_track(struct snd_compr_stream *stream)
{
	int retval;

	/* only a running stream can transition to next track */
	if (stream->runtime->state != SNDRV_PCM_STATE_RUNNING)
		return -EPERM;

	/* next track doesn't have any meaning for capture streams */
	if (stream->direction == SND_COMPRESS_CAPTURE)
		return -EPERM;

	/* you can signal next track if this is intended to be a gapless stream
	 * and current track metadata is set
	 */
	if (stream->metadata_set == false)
		return -EPERM;

	retval = stream->ops->trigger(stream, SND_COMPR_TRIGGER_NEXT_TRACK);
	if (retval != 0)
		return retval;
	stream->metadata_set = false;
	stream->next_track = true;
	return 0;
}
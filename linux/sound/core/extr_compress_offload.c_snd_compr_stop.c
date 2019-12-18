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
struct TYPE_4__ {int state; scalar_t__ total_bytes_transferred; scalar_t__ total_bytes_available; } ;
struct TYPE_3__ {int (* trigger ) (struct snd_compr_stream*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
#define  SNDRV_PCM_STATE_OPEN 130 
#define  SNDRV_PCM_STATE_PREPARED 129 
#define  SNDRV_PCM_STATE_SETUP 128 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  snd_compr_drain_notify (struct snd_compr_stream*) ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compr_stop(struct snd_compr_stream *stream)
{
	int retval;

	switch (stream->runtime->state) {
	case SNDRV_PCM_STATE_OPEN:
	case SNDRV_PCM_STATE_SETUP:
	case SNDRV_PCM_STATE_PREPARED:
		return -EPERM;
	default:
		break;
	}

	retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_STOP);
	if (!retval) {
		snd_compr_drain_notify(stream);
		stream->runtime->total_bytes_available = 0;
		stream->runtime->total_bytes_transferred = 0;
	}
	return retval;
}
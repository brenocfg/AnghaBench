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
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int (* trigger ) (struct snd_compr_stream*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SNDRV_PCM_STATE_PAUSED ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_PAUSE_RELEASE ; 
 int stub1 (struct snd_compr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compr_resume(struct snd_compr_stream *stream)
{
	int retval;

	if (stream->runtime->state != SNDRV_PCM_STATE_PAUSED)
		return -EPERM;
	retval = stream->ops->trigger(stream, SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
	if (!retval)
		stream->runtime->state = SNDRV_PCM_STATE_RUNNING;
	return retval;
}
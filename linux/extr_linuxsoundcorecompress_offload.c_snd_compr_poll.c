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
struct snd_compr_stream {TYPE_2__* device; TYPE_1__* runtime; } ;
struct snd_compr_file {struct snd_compr_stream stream; } ;
struct file {struct snd_compr_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int state; size_t fragment_size; int /*<<< orphan*/  sleep; } ;

/* Variables and functions */
 int EPOLLERR ; 
#define  SNDRV_PCM_STATE_DRAINING 133 
#define  SNDRV_PCM_STATE_OPEN 132 
#define  SNDRV_PCM_STATE_PAUSED 131 
#define  SNDRV_PCM_STATE_PREPARED 130 
#define  SNDRV_PCM_STATE_RUNNING 129 
 int SNDRV_PCM_STATE_SETUP ; 
#define  SNDRV_PCM_STATE_XRUN 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 size_t snd_compr_get_avail (struct snd_compr_stream*) ; 
 int snd_compr_get_poll (struct snd_compr_stream*) ; 

__attribute__((used)) static __poll_t snd_compr_poll(struct file *f, poll_table *wait)
{
	struct snd_compr_file *data = f->private_data;
	struct snd_compr_stream *stream;
	size_t avail;
	__poll_t retval = 0;

	if (snd_BUG_ON(!data))
		return EPOLLERR;

	stream = &data->stream;

	mutex_lock(&stream->device->lock);

	switch (stream->runtime->state) {
	case SNDRV_PCM_STATE_OPEN:
	case SNDRV_PCM_STATE_XRUN:
		retval = snd_compr_get_poll(stream) | EPOLLERR;
		goto out;
	default:
		break;
	}

	poll_wait(f, &stream->runtime->sleep, wait);

	avail = snd_compr_get_avail(stream);
	pr_debug("avail is %ld\n", (unsigned long)avail);
	/* check if we have at least one fragment to fill */
	switch (stream->runtime->state) {
	case SNDRV_PCM_STATE_DRAINING:
		/* stream has been woken up after drain is complete
		 * draining done so set stream state to stopped
		 */
		retval = snd_compr_get_poll(stream);
		stream->runtime->state = SNDRV_PCM_STATE_SETUP;
		break;
	case SNDRV_PCM_STATE_RUNNING:
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_PAUSED:
		if (avail >= stream->runtime->fragment_size)
			retval = snd_compr_get_poll(stream);
		break;
	default:
		retval = snd_compr_get_poll(stream) | EPOLLERR;
		break;
	}
out:
	mutex_unlock(&stream->device->lock);
	return retval;
}
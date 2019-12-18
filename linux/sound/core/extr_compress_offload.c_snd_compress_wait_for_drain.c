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
struct snd_compr_stream {TYPE_1__* device; TYPE_2__* runtime; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  sleep; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ SNDRV_PCM_STATE_DRAINING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_compress_wait_for_drain(struct snd_compr_stream *stream)
{
	int ret;

	/*
	 * We are called with lock held. So drop the lock while we wait for
	 * drain complete notification from the driver
	 *
	 * It is expected that driver will notify the drain completion and then
	 * stream will be moved to SETUP state, even if draining resulted in an
	 * error. We can trigger next track after this.
	 */
	stream->runtime->state = SNDRV_PCM_STATE_DRAINING;
	mutex_unlock(&stream->device->lock);

	/* we wait for drain to complete here, drain can return when
	 * interruption occurred, wait returned error or success.
	 * For the first two cases we don't do anything different here and
	 * return after waking up
	 */

	ret = wait_event_interruptible(stream->runtime->sleep,
			(stream->runtime->state != SNDRV_PCM_STATE_DRAINING));
	if (ret == -ERESTARTSYS)
		pr_debug("wait aborted by a signal\n");
	else if (ret)
		pr_debug("wait for drain failed with %d\n", ret);


	wake_up(&stream->runtime->sleep);
	mutex_lock(&stream->device->lock);

	return ret;
}
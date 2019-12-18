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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct snd_pcm_substream {int /*<<< orphan*/  pcm; struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {scalar_t__ buffer_used; int /*<<< orphan*/  buffer; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  sleep; TYPE_2__* status; TYPE_1__ oss; } ;
typedef  int ssize_t ;
typedef  scalar_t__ snd_pcm_state_t ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int HZ ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  pcm_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int snd_pcm_oss_write2 (struct snd_pcm_substream*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_oss_sync1(struct snd_pcm_substream *substream, size_t size)
{
	struct snd_pcm_runtime *runtime;
	ssize_t result = 0;
	snd_pcm_state_t state;
	long res;
	wait_queue_entry_t wait;

	runtime = substream->runtime;
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&runtime->sleep, &wait);
#ifdef OSS_DEBUG
	pcm_dbg(substream->pcm, "sync1: size = %li\n", size);
#endif
	while (1) {
		result = snd_pcm_oss_write2(substream, runtime->oss.buffer, size, 1);
		if (result > 0) {
			runtime->oss.buffer_used = 0;
			result = 0;
			break;
		}
		if (result != 0 && result != -EAGAIN)
			break;
		result = 0;
		set_current_state(TASK_INTERRUPTIBLE);
		snd_pcm_stream_lock_irq(substream);
		state = runtime->status->state;
		snd_pcm_stream_unlock_irq(substream);
		if (state != SNDRV_PCM_STATE_RUNNING) {
			set_current_state(TASK_RUNNING);
			break;
		}
		res = schedule_timeout(10 * HZ);
		if (signal_pending(current)) {
			result = -ERESTARTSYS;
			break;
		}
		if (res == 0) {
			pcm_err(substream->pcm,
				"OSS sync error - DMA timeout\n");
			result = -EIO;
			break;
		}
	}
	remove_wait_queue(&runtime->sleep, &wait);
	return result;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct snd_sof_dev {int dtrace_draining; int /*<<< orphan*/  trace_sleep; int /*<<< orphan*/  dtrace_is_enabled; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 size_t sof_trace_avail (struct snd_sof_dev*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static size_t sof_wait_trace_avail(struct snd_sof_dev *sdev,
				   loff_t pos, size_t buffer_size)
{
	wait_queue_entry_t wait;
	size_t ret = sof_trace_avail(sdev, pos, buffer_size);

	/* data immediately available */
	if (ret)
		return ret;

	if (!sdev->dtrace_is_enabled && sdev->dtrace_draining) {
		/*
		 * tracing has ended and all traces have been
		 * read by client, return EOF
		 */
		sdev->dtrace_draining = false;
		return 0;
	}

	/* wait for available trace data from FW */
	init_waitqueue_entry(&wait, current);
	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&sdev->trace_sleep, &wait);

	if (!signal_pending(current)) {
		/* set timeout to max value, no error code */
		schedule_timeout(MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(&sdev->trace_sleep, &wait);

	return sof_trace_avail(sdev, pos, buffer_size);
}
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
struct amdtp_stream {int /*<<< orphan*/  pcm_buffer_pointer; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ amdtp_stream_running (struct amdtp_stream*) ; 
 int /*<<< orphan*/  fw_iso_context_flush_completions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 

unsigned long amdtp_stream_pcm_pointer(struct amdtp_stream *s)
{
	/*
	 * This function is called in software IRQ context of period_tasklet or
	 * process context.
	 *
	 * When the software IRQ context was scheduled by software IRQ context
	 * of IR/IT contexts, queued packets were already handled. Therefore,
	 * no need to flush the queue in buffer anymore.
	 *
	 * When the process context reach here, some packets will be already
	 * queued in the buffer. These packets should be handled immediately
	 * to keep better granularity of PCM pointer.
	 *
	 * Later, the process context will sometimes schedules software IRQ
	 * context of the period_tasklet. Then, no need to flush the queue by
	 * the same reason as described for IR/IT contexts.
	 */
	if (!in_interrupt() && amdtp_stream_running(s))
		fw_iso_context_flush_completions(s->context);

	return READ_ONCE(s->pcm_buffer_pointer);
}
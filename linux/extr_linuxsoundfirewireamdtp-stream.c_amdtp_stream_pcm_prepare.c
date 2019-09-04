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
struct amdtp_stream {scalar_t__ pcm_period_pointer; scalar_t__ pcm_buffer_pointer; int /*<<< orphan*/  period_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void amdtp_stream_pcm_prepare(struct amdtp_stream *s)
{
	tasklet_kill(&s->period_tasklet);
	s->pcm_buffer_pointer = 0;
	s->pcm_period_pointer = 0;
}
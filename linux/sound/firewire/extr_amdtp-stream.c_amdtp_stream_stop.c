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
struct amdtp_stream {int callbacked; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pkt_descs; int /*<<< orphan*/  unit; int /*<<< orphan*/  buffer; int /*<<< orphan*/  context; int /*<<< orphan*/  period_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  amdtp_stream_running (struct amdtp_stream*) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_packets_buffer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdtp_stream_stop(struct amdtp_stream *s)
{
	mutex_lock(&s->mutex);

	if (!amdtp_stream_running(s)) {
		mutex_unlock(&s->mutex);
		return;
	}

	tasklet_kill(&s->period_tasklet);
	fw_iso_context_stop(s->context);
	fw_iso_context_destroy(s->context);
	s->context = ERR_PTR(-1);
	iso_packets_buffer_destroy(&s->buffer, s->unit);
	kfree(s->pkt_descs);

	s->callbacked = false;

	mutex_unlock(&s->mutex);
}
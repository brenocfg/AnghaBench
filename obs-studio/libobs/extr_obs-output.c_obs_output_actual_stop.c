#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* stop ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {TYPE_12__* caption_tail; TYPE_12__* caption_head; int /*<<< orphan*/  stopping_event; void* stop_code; TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  delay_capturing; int /*<<< orphan*/  delay_active; int /*<<< orphan*/  reconnect_thread; scalar_t__ reconnect_thread_active; int /*<<< orphan*/  reconnect_stop_event; } ;
typedef  TYPE_3__ obs_output_t ;
struct TYPE_13__ {struct TYPE_13__* next; } ;

/* Variables and functions */
 void* OBS_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  bfree (TYPE_12__*) ; 
 scalar_t__ delay_active (TYPE_3__*) ; 
 int delay_capturing (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_output_pause (TYPE_3__*,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ reconnecting (TYPE_3__*) ; 
 int /*<<< orphan*/  signal_stop (TYPE_3__*) ; 
 scalar_t__ stopping (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

void obs_output_actual_stop(obs_output_t *output, bool force, uint64_t ts)
{
	bool call_stop = true;
	bool was_reconnecting = false;

	if (stopping(output) && !force)
		return;

	obs_output_pause(output, false);

	os_event_reset(output->stopping_event);

	was_reconnecting = reconnecting(output) && !delay_active(output);
	if (reconnecting(output)) {
		os_event_signal(output->reconnect_stop_event);
		if (output->reconnect_thread_active)
			pthread_join(output->reconnect_thread, NULL);
	}

	if (force) {
		if (delay_active(output)) {
			call_stop = delay_capturing(output);
			os_atomic_set_bool(&output->delay_active, false);
			os_atomic_set_bool(&output->delay_capturing, false);
			output->stop_code = OBS_OUTPUT_SUCCESS;
			obs_output_end_data_capture(output);
			os_event_signal(output->stopping_event);
		} else {
			call_stop = true;
		}
	} else {
		call_stop = true;
	}

	if (output->context.data && call_stop) {
		output->info.stop(output->context.data, ts);

	} else if (was_reconnecting) {
		output->stop_code = OBS_OUTPUT_SUCCESS;
		signal_stop(output);
		os_event_signal(output->stopping_event);
	}

	while (output->caption_head) {
		output->caption_tail = output->caption_head->next;
		bfree(output->caption_head);
		output->caption_head = output->caption_tail;
	}
}
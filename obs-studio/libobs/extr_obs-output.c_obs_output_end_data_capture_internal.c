#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {void* stop_code; TYPE_1__ context; int /*<<< orphan*/  end_data_capture_thread; int /*<<< orphan*/  end_data_capture_thread_active; scalar_t__ video; int /*<<< orphan*/  data_active; int /*<<< orphan*/  stopping_event; int /*<<< orphan*/  delay_active; int /*<<< orphan*/  delay_restart_refs; int /*<<< orphan*/  delay_capturing; } ;
typedef  TYPE_2__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 void* OBS_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  active (TYPE_2__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_active (TYPE_2__*) ; 
 scalar_t__ data_capture_ending (TYPE_2__*) ; 
 scalar_t__ delay_active (TYPE_2__*) ; 
 int /*<<< orphan*/  end_data_capture_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  log_frame_info (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  os_atomic_load_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_2__*),TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_stop (TYPE_2__*) ; 

__attribute__((used)) static void obs_output_end_data_capture_internal(obs_output_t *output,
						 bool signal)
{
	int ret;

	if (!obs_output_valid(output, "obs_output_end_data_capture"))
		return;

	if (!active(output) || !data_active(output)) {
		if (signal) {
			signal_stop(output);
			output->stop_code = OBS_OUTPUT_SUCCESS;
			os_event_signal(output->stopping_event);
		}
		return;
	}

	if (delay_active(output)) {
		os_atomic_set_bool(&output->delay_capturing, false);

		if (!os_atomic_load_long(&output->delay_restart_refs)) {
			os_atomic_set_bool(&output->delay_active, false);
		} else {
			os_event_signal(output->stopping_event);
			return;
		}
	}

	os_atomic_set_bool(&output->data_active, false);

	if (output->video)
		log_frame_info(output);

	if (data_capture_ending(output))
		pthread_join(output->end_data_capture_thread, NULL);

	os_atomic_set_bool(&output->end_data_capture_thread_active, true);
	ret = pthread_create(&output->end_data_capture_thread, NULL,
			     end_data_capture_thread, output);
	if (ret != 0) {
		blog(LOG_WARNING,
		     "Failed to create end_data_capture_thread "
		     "for output '%s'!",
		     output->context.name);
		end_data_capture_thread(output);
	}

	if (signal) {
		signal_stop(output);
		output->stop_code = OBS_OUTPUT_SUCCESS;
	}
}
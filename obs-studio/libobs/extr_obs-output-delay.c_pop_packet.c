#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ size; } ;
struct obs_output {int delay_cur_flags; scalar_t__ active_delay_ns; int /*<<< orphan*/  delay_mutex; TYPE_1__ delay_data; scalar_t__ reconnecting; } ;
struct delay_data {scalar_t__ ts; } ;
typedef  int /*<<< orphan*/  dd ;

/* Variables and functions */
 int OBS_OUTPUT_DELAY_PRESERVE ; 
 int /*<<< orphan*/  circlebuf_peek_front (TYPE_1__*,struct delay_data*,int) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_delay_data (struct obs_output*,struct delay_data*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool pop_packet(struct obs_output *output, uint64_t t)
{
	uint64_t elapsed_time;
	struct delay_data dd;
	bool popped = false;
	bool preserve;

	/* ------------------------------------------------ */

	preserve = (output->delay_cur_flags & OBS_OUTPUT_DELAY_PRESERVE) != 0;

	pthread_mutex_lock(&output->delay_mutex);

	if (output->delay_data.size) {
		circlebuf_peek_front(&output->delay_data, &dd, sizeof(dd));
		elapsed_time = (t - dd.ts);

		if (preserve && output->reconnecting) {
			output->active_delay_ns = elapsed_time;

		} else if (elapsed_time > output->active_delay_ns) {
			circlebuf_pop_front(&output->delay_data, NULL,
					    sizeof(dd));
			popped = true;
		}
	}

	pthread_mutex_unlock(&output->delay_mutex);

	/* ------------------------------------------------ */

	if (popped)
		process_delay_data(output, &dd);

	return popped;
}
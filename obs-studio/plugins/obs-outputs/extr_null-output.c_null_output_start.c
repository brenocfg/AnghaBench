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
struct null_output {int /*<<< orphan*/  output; int /*<<< orphan*/  stop_thread; scalar_t__ stop_thread_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_initialize_encoders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool null_output_start(void *data)
{
	struct null_output *context = data;

	if (!obs_output_can_begin_data_capture(context->output, 0))
		return false;
	if (!obs_output_initialize_encoders(context->output, 0))
		return false;

	if (context->stop_thread_active)
		pthread_join(context->stop_thread, NULL);

	obs_output_begin_data_capture(context->output, 0);
	return true;
}
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
struct null_output {int stop_thread_active; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *stop_thread(void *data)
{
	struct null_output *context = data;
	obs_output_end_data_capture(context->output);
	context->stop_thread_active = false;
	return NULL;
}
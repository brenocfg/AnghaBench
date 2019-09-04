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
struct null_output {int /*<<< orphan*/  stop_thread; scalar_t__ stop_thread_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct null_output*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void null_output_destroy(void *data)
{
	struct null_output *context = data;
	if (context->stop_thread_active)
		pthread_join(context->stop_thread, NULL);
	bfree(context);
}
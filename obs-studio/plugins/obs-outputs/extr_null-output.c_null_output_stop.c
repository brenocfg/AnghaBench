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
typedef  int /*<<< orphan*/  uint64_t ;
struct null_output {int stop_thread_active; int /*<<< orphan*/  stop_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stop_thread ; 

__attribute__((used)) static void null_output_stop(void *data, uint64_t ts)
{
	struct null_output *context = data;
	UNUSED_PARAMETER(ts);

	context->stop_thread_active = pthread_create(&context->stop_thread,
						     NULL, stop_thread,
						     data) == 0;
}
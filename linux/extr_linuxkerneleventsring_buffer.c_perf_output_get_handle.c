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
struct ring_buffer {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  nest; } ;
struct perf_output_handle {int /*<<< orphan*/  wakeup; struct ring_buffer* rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 

__attribute__((used)) static void perf_output_get_handle(struct perf_output_handle *handle)
{
	struct ring_buffer *rb = handle->rb;

	preempt_disable();
	local_inc(&rb->nest);
	handle->wakeup = local_read(&rb->wakeup);
}
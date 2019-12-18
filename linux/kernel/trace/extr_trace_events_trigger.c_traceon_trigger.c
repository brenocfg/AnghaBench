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
struct ring_buffer_event {int dummy; } ;
struct event_trigger_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ tracing_is_on () ; 
 int /*<<< orphan*/  tracing_on () ; 

__attribute__((used)) static void
traceon_trigger(struct event_trigger_data *data, void *rec,
		struct ring_buffer_event *event)
{
	if (tracing_is_on())
		return;

	tracing_on();
}
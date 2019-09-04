#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_event_buffer {int /*<<< orphan*/  pc; int /*<<< orphan*/  flags; int /*<<< orphan*/  entry; int /*<<< orphan*/  event; int /*<<< orphan*/  buffer; int /*<<< orphan*/  trace_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_trigger_unlock_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_printk (struct trace_event_buffer*) ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 
 TYPE_1__ tracepoint_printk_key ; 

void trace_event_buffer_commit(struct trace_event_buffer *fbuffer)
{
	if (static_key_false(&tracepoint_printk_key.key))
		output_printk(fbuffer);

	event_trigger_unlock_commit(fbuffer->trace_file, fbuffer->buffer,
				    fbuffer->event, fbuffer->entry,
				    fbuffer->flags, fbuffer->pc);
}
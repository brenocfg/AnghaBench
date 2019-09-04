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
struct trace_export {int /*<<< orphan*/  (* write ) (struct trace_export*,struct trace_entry*,unsigned int) ;} ;
struct trace_entry {int dummy; } ;
struct ring_buffer_event {int dummy; } ;

/* Variables and functions */
 struct trace_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 unsigned int ring_buffer_event_length (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  stub1 (struct trace_export*,struct trace_entry*,unsigned int) ; 

__attribute__((used)) static void
trace_process_export(struct trace_export *export,
	       struct ring_buffer_event *event)
{
	struct trace_entry *entry;
	unsigned int size = 0;

	entry = ring_buffer_event_data(event);
	size = ring_buffer_event_length(event);
	export->write(export, entry, size);
}
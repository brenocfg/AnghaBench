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
struct trace_array {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_buffer_unlock_commit_regs (struct trace_array*,struct ring_buffer*,struct ring_buffer_event*,unsigned long,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void trace_buffer_unlock_commit(struct trace_array *tr,
					      struct ring_buffer *buffer,
					      struct ring_buffer_event *event,
					      unsigned long flags, int pc)
{
	trace_buffer_unlock_commit_regs(tr, buffer, event, flags, pc, NULL);
}
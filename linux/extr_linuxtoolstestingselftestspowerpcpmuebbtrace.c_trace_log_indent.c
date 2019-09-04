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
struct trace_entry {int /*<<< orphan*/  type; } ;
struct trace_buffer {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  TRACE_TYPE_INDENT ; 
 struct trace_entry* trace_alloc_entry (struct trace_buffer*,int /*<<< orphan*/ ) ; 

int trace_log_indent(struct trace_buffer *tb)
{
	struct trace_entry *e;

	e = trace_alloc_entry(tb, 0);
	if (!e)
		return -ENOSPC;

	e->type = TRACE_TYPE_INDENT;

	return 0;
}
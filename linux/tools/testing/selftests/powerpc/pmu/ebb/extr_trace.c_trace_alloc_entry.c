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
struct trace_entry {int length; } ;
struct trace_buffer {int dummy; } ;

/* Variables and functions */
 struct trace_entry* trace_alloc (struct trace_buffer*,int) ; 

__attribute__((used)) static struct trace_entry *trace_alloc_entry(struct trace_buffer *tb, int payload_size)
{
	struct trace_entry *e;

	e = trace_alloc(tb, sizeof(*e) + payload_size);
	if (e)
		e->length = payload_size;

	return e;
}
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
struct trace_buffer {void* tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_check_alloc (struct trace_buffer*,void*) ; 

__attribute__((used)) static void *trace_alloc(struct trace_buffer *tb, int bytes)
{
	void *p, *newtail;

	p = tb->tail;
	newtail = tb->tail + bytes;
	if (!trace_check_alloc(tb, newtail))
		return NULL;

	tb->tail = newtail;

	return p;
}
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
struct trace_buffer {void* tail; void* data; scalar_t__ overflow; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int BASE_PREFIX ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ trace_check_bounds (struct trace_buffer*,void*) ; 
 int /*<<< orphan*/  trace_print_entry (struct trace_entry*,int,int*) ; 

void trace_buffer_print(struct trace_buffer *tb)
{
	struct trace_entry *e;
	int i, prefix;
	void *p;

	printf("Trace buffer dump:\n");
	printf("  address  %p \n", tb);
	printf("  tail     %p\n", tb->tail);
	printf("  size     %llu\n", tb->size);
	printf("  overflow %s\n", tb->overflow ? "TRUE" : "false");
	printf("  Content:\n");

	p = tb->data;

	i = 0;
	prefix = BASE_PREFIX;

	while (trace_check_bounds(tb, p) && p < tb->tail) {
		e = p;

		trace_print_entry(e, i, &prefix);

		i++;
		p = (void *)e + sizeof(*e) + e->length;
	}
}
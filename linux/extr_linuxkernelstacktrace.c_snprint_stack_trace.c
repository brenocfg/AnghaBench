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
struct stack_trace {int nr_entries; scalar_t__* entries; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int snprintf (char*,size_t,char*,int,char,void*) ; 

int snprint_stack_trace(char *buf, size_t size,
			struct stack_trace *trace, int spaces)
{
	int i;
	int generated;
	int total = 0;

	if (WARN_ON(!trace->entries))
		return 0;

	for (i = 0; i < trace->nr_entries; i++) {
		generated = snprintf(buf, size, "%*c%pS\n", 1 + spaces, ' ',
				     (void *)trace->entries[i]);

		total += generated;

		/* Assume that generated isn't a negative number */
		if (generated >= size) {
			buf += size;
			size = 0;
		} else {
			buf += generated;
			size -= generated;
		}
	}

	return total;
}
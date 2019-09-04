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
struct stack_trace {int nr_entries; unsigned long* entries; } ;

/* Variables and functions */

__attribute__((used)) static inline bool check_recursive_alloc(struct stack_trace *trace,
					unsigned long ip)
{
	int i;

	if (!trace->nr_entries)
		return false;

	for (i = 0; i < trace->nr_entries; i++) {
		if (trace->entries[i] == ip)
			return true;
	}

	return false;
}
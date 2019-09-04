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
struct trace_array {int* trace_flags_index; } ;

/* Variables and functions */
 int TRACE_FLAGS_MAX_SIZE ; 

__attribute__((used)) static void init_trace_flags_index(struct trace_array *tr)
{
	int i;

	/* Used by the trace options files */
	for (i = 0; i < TRACE_FLAGS_MAX_SIZE; i++)
		tr->trace_flags_index[i] = i;
}
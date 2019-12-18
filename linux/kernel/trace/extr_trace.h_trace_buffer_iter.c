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
struct trace_iterator {struct ring_buffer_iter** buffer_iter; } ;
struct ring_buffer_iter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ring_buffer_iter *
trace_buffer_iter(struct trace_iterator *iter, int cpu)
{
	return iter->buffer_iter ? iter->buffer_iter[cpu] : NULL;
}
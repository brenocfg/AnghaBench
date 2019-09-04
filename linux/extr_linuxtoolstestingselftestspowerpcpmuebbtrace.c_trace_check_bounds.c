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
struct trace_buffer {int size; } ;

/* Variables and functions */

__attribute__((used)) static bool trace_check_bounds(struct trace_buffer *tb, void *p)
{
	return p < ((void *)tb + tb->size);
}
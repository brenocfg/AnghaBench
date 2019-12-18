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

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int stack_trace_save (unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __save_stack_trace(unsigned long *trace)
{
	return stack_trace_save(trace, MAX_TRACE, 2);
}
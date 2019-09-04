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
typedef  int /*<<< orphan*/  initcall_t ;

/* Variables and functions */
 int /*<<< orphan*/  initcall_calltime ; 
 int /*<<< orphan*/  initcall_debug ; 
 int /*<<< orphan*/  trace_initcall_start_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void do_trace_initcall_start(initcall_t fn)
{
	if (!initcall_debug)
		return;
	trace_initcall_start_cb(&initcall_calltime, fn);
}
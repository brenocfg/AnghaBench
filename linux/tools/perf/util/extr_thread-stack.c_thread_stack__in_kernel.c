#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_stack {int cnt; TYPE_2__* stack; } ;
struct TYPE_4__ {TYPE_1__* cp; } ;
struct TYPE_3__ {int in_kernel; } ;

/* Variables and functions */

__attribute__((used)) static bool thread_stack__in_kernel(struct thread_stack *ts)
{
	if (!ts->cnt)
		return false;

	return ts->stack[ts->cnt - 1].cp->in_kernel;
}
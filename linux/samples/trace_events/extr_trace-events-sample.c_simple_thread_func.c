#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cpus_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/ * random_strings ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_foo_bar (char*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_foo_bar_with_cond (char*,int) ; 
 int /*<<< orphan*/  trace_foo_with_template_cond (char*,int) ; 
 int /*<<< orphan*/  trace_foo_with_template_print (char*,int) ; 
 int /*<<< orphan*/  trace_foo_with_template_simple (char*,int) ; 

__attribute__((used)) static void simple_thread_func(int cnt)
{
	int array[6];
	int len = cnt % 5;
	int i;

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ);

	for (i = 0; i < len; i++)
		array[i] = i + 1;
	array[i] = 0;

	/* Silly tracepoints */
	trace_foo_bar("hello", cnt, array, random_strings[len],
		      current->cpus_ptr);

	trace_foo_with_template_simple("HELLO", cnt);

	trace_foo_bar_with_cond("Some times print", cnt);

	trace_foo_with_template_cond("prints other times", cnt);

	trace_foo_with_template_print("I have to be different", cnt);
}
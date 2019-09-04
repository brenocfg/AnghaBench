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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_is_dead () ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void test_ftrace_alive(struct seq_file *m)
{
	if (!ftrace_is_dead())
		return;
	seq_puts(m, "# WARNING: FUNCTION TRACING IS CORRUPTED\n"
		    "#          MAY BE MISSING FUNCTION EVENTS\n");
}
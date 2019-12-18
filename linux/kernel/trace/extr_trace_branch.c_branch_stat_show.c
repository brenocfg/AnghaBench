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
struct ftrace_branch_data {int /*<<< orphan*/  line; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 long get_incorrect_percent (struct ftrace_branch_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void branch_stat_show(struct seq_file *m,
			     struct ftrace_branch_data *p, const char *f)
{
	long percent;

	/*
	 * The miss is overlayed on correct, and hit on incorrect.
	 */
	percent = get_incorrect_percent(p);

	if (percent < 0)
		seq_puts(m, "  X ");
	else
		seq_printf(m, "%3ld ", percent);

	seq_printf(m, "%-30.30s %-20.20s %d\n", p->func, f, p->line);
}
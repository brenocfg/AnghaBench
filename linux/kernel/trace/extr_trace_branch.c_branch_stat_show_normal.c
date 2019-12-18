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
struct ftrace_branch_data {int /*<<< orphan*/  incorrect; int /*<<< orphan*/  correct; } ;

/* Variables and functions */
 int /*<<< orphan*/  branch_stat_show (struct seq_file*,struct ftrace_branch_data*,char const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int branch_stat_show_normal(struct seq_file *m,
				   struct ftrace_branch_data *p, const char *f)
{
	seq_printf(m, "%8lu %8lu ",  p->correct, p->incorrect);
	branch_stat_show(m, p, f);
	return 0;
}
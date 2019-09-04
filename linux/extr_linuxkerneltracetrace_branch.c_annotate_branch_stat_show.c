#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  incorrect; int /*<<< orphan*/  correct; } ;
struct ftrace_likely_data {TYPE_1__ data; int /*<<< orphan*/  constant; } ;

/* Variables and functions */
 char* branch_stat_process_file (TYPE_1__*) ; 
 int /*<<< orphan*/  branch_stat_show (struct seq_file*,TYPE_1__*,char const*) ; 
 int branch_stat_show_normal (struct seq_file*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int annotate_branch_stat_show(struct seq_file *m, void *v)
{
	struct ftrace_likely_data *p = v;
	const char *f;
	int l;

	f = branch_stat_process_file(&p->data);

	if (!p->constant)
		return branch_stat_show_normal(m, &p->data, f);

	l = snprintf(NULL, 0, "/%lu", p->constant);
	l = l > 8 ? 0 : 8 - l;

	seq_printf(m, "%8lu/%lu %*lu ",
		   p->data.correct, p->constant, l, p->data.incorrect);
	branch_stat_show(m, &p->data, f);
	return 0;
}
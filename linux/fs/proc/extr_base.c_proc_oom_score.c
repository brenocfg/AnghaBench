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
struct task_struct {int dummy; } ;
struct seq_file {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int oom_badness (struct task_struct*,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 
 unsigned long total_swap_pages ; 
 unsigned long totalram_pages () ; 

__attribute__((used)) static int proc_oom_score(struct seq_file *m, struct pid_namespace *ns,
			  struct pid *pid, struct task_struct *task)
{
	unsigned long totalpages = totalram_pages() + total_swap_pages;
	unsigned long points = 0;

	points = oom_badness(task, totalpages) * 1000 / totalpages;
	seq_printf(m, "%lu\n", points);

	return 0;
}
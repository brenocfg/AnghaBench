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
struct seq_file {struct kernfs_open_file* private; } ;
struct kernfs_open_file {struct css_task_iter* priv; } ;
struct css_task_iter {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* css_task_iter_next (struct css_task_iter*) ; 

__attribute__((used)) static void *cgroup_procs_next(struct seq_file *s, void *v, loff_t *pos)
{
	struct kernfs_open_file *of = s->private;
	struct css_task_iter *it = of->priv;

	return css_task_iter_next(it);
}
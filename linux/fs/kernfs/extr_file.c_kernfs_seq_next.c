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
struct kernfs_ops {void* (* seq_next ) (struct seq_file*,void*,int /*<<< orphan*/ *) ;} ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct kernfs_ops* kernfs_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_seq_stop_active (struct seq_file*,void*) ; 
 void* stub1 (struct seq_file*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *kernfs_seq_next(struct seq_file *sf, void *v, loff_t *ppos)
{
	struct kernfs_open_file *of = sf->private;
	const struct kernfs_ops *ops = kernfs_ops(of->kn);

	if (ops->seq_next) {
		void *next = ops->seq_next(sf, v, ppos);
		/* see the comment above kernfs_seq_stop_active() */
		if (next == ERR_PTR(-ENODEV))
			kernfs_seq_stop_active(sf, next);
		return next;
	} else {
		/*
		 * The same behavior and code as single_open(), always
		 * terminate after the initial read.
		 */
		++*ppos;
		return NULL;
	}
}
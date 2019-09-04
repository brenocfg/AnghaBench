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
struct kernfs_ops {int /*<<< orphan*/  (* seq_stop ) (struct seq_file*,void*) ;} ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;

/* Variables and functions */
 struct kernfs_ops* kernfs_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*,void*) ; 

__attribute__((used)) static void kernfs_seq_stop_active(struct seq_file *sf, void *v)
{
	struct kernfs_open_file *of = sf->private;
	const struct kernfs_ops *ops = kernfs_ops(of->kn);

	if (ops->seq_stop)
		ops->seq_stop(sf, v);
	kernfs_put_active(of->kn);
}
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
struct trace_subsystem_dir {struct trace_array* tr; } ;
struct trace_array {int dummy; } ;
struct inode {struct trace_array* i_private; } ;
struct file {struct trace_subsystem_dir* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct trace_subsystem_dir*) ; 
 struct trace_subsystem_dir* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ trace_array_get (struct trace_array*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 scalar_t__ tracing_is_disabled () ; 
 int tracing_open_generic (struct inode*,struct file*) ; 

__attribute__((used)) static int system_tr_open(struct inode *inode, struct file *filp)
{
	struct trace_subsystem_dir *dir;
	struct trace_array *tr = inode->i_private;
	int ret;

	if (tracing_is_disabled())
		return -ENODEV;

	if (trace_array_get(tr) < 0)
		return -ENODEV;

	/* Make a temporary dir that has no system but points to tr */
	dir = kzalloc(sizeof(*dir), GFP_KERNEL);
	if (!dir) {
		trace_array_put(tr);
		return -ENOMEM;
	}

	dir->tr = tr;

	ret = tracing_open_generic(inode, filp);
	if (ret < 0) {
		trace_array_put(tr);
		kfree(dir);
		return ret;
	}

	filp->private_data = dir;

	return 0;
}
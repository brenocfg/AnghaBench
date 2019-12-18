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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct trace_subsystem_dir*) ; 
 struct trace_subsystem_dir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tracing_open_generic_tr (struct inode*,struct file*) ; 

__attribute__((used)) static int system_tr_open(struct inode *inode, struct file *filp)
{
	struct trace_subsystem_dir *dir;
	struct trace_array *tr = inode->i_private;
	int ret;

	/* Make a temporary dir that has no system but points to tr */
	dir = kzalloc(sizeof(*dir), GFP_KERNEL);
	if (!dir)
		return -ENOMEM;

	ret = tracing_open_generic_tr(inode, filp);
	if (ret < 0) {
		kfree(dir);
		return ret;
	}
	dir->tr = tr;
	filp->private_data = dir;

	return 0;
}
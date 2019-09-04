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
struct proc_data {struct proc_data* wbuffer; struct proc_data* rbuffer; int /*<<< orphan*/  (* on_close ) (struct inode*,struct file*) ;} ;
struct inode {int dummy; } ;
struct file {struct proc_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct proc_data*) ; 
 int /*<<< orphan*/  stub1 (struct inode*,struct file*) ; 

__attribute__((used)) static int proc_close( struct inode *inode, struct file *file )
{
	struct proc_data *data = file->private_data;

	if (data->on_close != NULL)
		data->on_close(inode, file);
	kfree(data->rbuffer);
	kfree(data->wbuffer);
	kfree(data);
	return 0;
}
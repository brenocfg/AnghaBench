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
struct inode {struct controller* i_private; } ;
struct file {struct ctrl_dbg* private_data; } ;
struct ctrl_dbg {void* data; int /*<<< orphan*/  size; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OUTPUT ; 
 int /*<<< orphan*/  cpqphp_mutex ; 
 int /*<<< orphan*/  kfree (struct ctrl_dbg*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spew_debug_info (struct controller*,void*,int) ; 

__attribute__((used)) static int open(struct inode *inode, struct file *file)
{
	struct controller *ctrl = inode->i_private;
	struct ctrl_dbg *dbg;
	int retval = -ENOMEM;

	mutex_lock(&cpqphp_mutex);
	dbg = kmalloc(sizeof(*dbg), GFP_KERNEL);
	if (!dbg)
		goto exit;
	dbg->data = kmalloc(MAX_OUTPUT, GFP_KERNEL);
	if (!dbg->data) {
		kfree(dbg);
		goto exit;
	}
	dbg->size = spew_debug_info(ctrl, dbg->data, MAX_OUTPUT);
	file->private_data = dbg;
	retval = 0;
exit:
	mutex_unlock(&cpqphp_mutex);
	return retval;
}
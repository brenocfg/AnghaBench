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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  hmcdrv_ftp_shutdown () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct file*) ; 

__attribute__((used)) static int hmcdrv_dev_release(struct inode *inode, struct file *fp)
{
	pr_debug("closing file '/dev/%pD'\n", fp);
	kfree(fp->private_data);
	fp->private_data = NULL;
	hmcdrv_ftp_shutdown();
	module_put(THIS_MODULE);
	return 0;
}
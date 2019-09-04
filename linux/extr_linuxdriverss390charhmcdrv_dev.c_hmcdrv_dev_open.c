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
struct file {int f_flags; int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int O_ACCMODE ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int hmcdrv_ftp_startup () ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct file*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hmcdrv_dev_open(struct inode *inode, struct file *fp)
{
	int rc;

	/* check for non-blocking access, which is really unsupported
	 */
	if (fp->f_flags & O_NONBLOCK)
		return -EINVAL;

	/* Because it makes no sense to open this device read-only (then a
	 * FTP command cannot be emitted), we respond with an error.
	 */
	if ((fp->f_flags & O_ACCMODE) == O_RDONLY)
		return -EINVAL;

	/* prevent unloading this module as long as anyone holds the
	 * device file open - so increment the reference count here
	 */
	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	fp->private_data = NULL; /* no command yet */
	rc = hmcdrv_ftp_startup();
	if (rc)
		module_put(THIS_MODULE);

	pr_debug("open file '/dev/%pD' with return code %d\n", fp, rc);
	return rc;
}
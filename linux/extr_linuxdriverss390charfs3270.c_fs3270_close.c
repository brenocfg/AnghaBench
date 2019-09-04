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
struct fs3270 {int /*<<< orphan*/  view; int /*<<< orphan*/ * fs_pid; } ;
struct file {struct fs3270* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_del_view (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_put_view (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fs3270_close(struct inode *inode, struct file *filp)
{
	struct fs3270 *fp;

	fp = filp->private_data;
	filp->private_data = NULL;
	if (fp) {
		put_pid(fp->fs_pid);
		fp->fs_pid = NULL;
		raw3270_reset(&fp->view);
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
	}
	return 0;
}
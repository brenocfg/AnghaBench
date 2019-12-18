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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct gfs2_file {int /*<<< orphan*/  f_fl_mutex; } ;
struct file {struct gfs2_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int generic_file_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  gfs2_assert_warn (int /*<<< orphan*/ ,int) ; 
 struct gfs2_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int gfs2_open_common(struct inode *inode, struct file *file)
{
	struct gfs2_file *fp;
	int ret;

	if (S_ISREG(inode->i_mode)) {
		ret = generic_file_open(inode, file);
		if (ret)
			return ret;
	}

	fp = kzalloc(sizeof(struct gfs2_file), GFP_NOFS);
	if (!fp)
		return -ENOMEM;

	mutex_init(&fp->f_fl_mutex);

	gfs2_assert_warn(GFS2_SB(inode), !file->private_data);
	file->private_data = fp;
	return 0;
}
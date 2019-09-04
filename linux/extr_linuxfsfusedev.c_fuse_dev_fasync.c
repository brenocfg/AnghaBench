#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fuse_dev {TYPE_2__* fc; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fasync; } ;
struct TYPE_4__ {TYPE_1__ iq; } ;

/* Variables and functions */
 int EPERM ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 struct fuse_dev* fuse_get_dev (struct file*) ; 

__attribute__((used)) static int fuse_dev_fasync(int fd, struct file *file, int on)
{
	struct fuse_dev *fud = fuse_get_dev(file);

	if (!fud)
		return -EPERM;

	/* No locking - fasync_helper does its own locking */
	return fasync_helper(fd, file, on, &fud->fc->iq.fasync);
}
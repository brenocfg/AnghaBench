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
struct fuse_dev {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  dev_count; } ;
struct file {struct fuse_dev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct fuse_dev* fuse_dev_alloc_install (struct fuse_conn*) ; 

__attribute__((used)) static int fuse_device_clone(struct fuse_conn *fc, struct file *new)
{
	struct fuse_dev *fud;

	if (new->private_data)
		return -EINVAL;

	fud = fuse_dev_alloc_install(fc);
	if (!fud)
		return -ENOMEM;

	new->private_data = fud;
	atomic_inc(&fc->dev_count);

	return 0;
}
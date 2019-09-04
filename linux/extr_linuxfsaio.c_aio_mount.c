#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_system_type {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_RING_MAGIC ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  SB_I_NOEXEC ; 
 struct dentry* mount_pseudo (struct file_system_type*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *aio_mount(struct file_system_type *fs_type,
				int flags, const char *dev_name, void *data)
{
	struct dentry *root = mount_pseudo(fs_type, "aio:", NULL, NULL,
					   AIO_RING_MAGIC);

	if (!IS_ERR(root))
		root->d_sb->s_iflags |= SB_I_NOEXEC;
	return root;
}
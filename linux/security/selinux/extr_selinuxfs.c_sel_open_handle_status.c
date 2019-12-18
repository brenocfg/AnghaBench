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
struct selinux_fs_info {int /*<<< orphan*/  state; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct page* private_data; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {struct selinux_fs_info* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* file_inode (struct file*) ; 
 struct page* selinux_kernel_status_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_open_handle_status(struct inode *inode, struct file *filp)
{
	struct selinux_fs_info *fsi = file_inode(filp)->i_sb->s_fs_info;
	struct page    *status = selinux_kernel_status_page(fsi->state);

	if (!status)
		return -ENOMEM;

	filp->private_data = status;

	return 0;
}
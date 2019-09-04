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
struct selinux_fs_info {scalar_t__ policy_opened; } ;
struct policy_load_memory {int /*<<< orphan*/  data; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {struct policy_load_memory* private_data; } ;
struct TYPE_2__ {struct selinux_fs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct policy_load_memory*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_release_policy(struct inode *inode, struct file *filp)
{
	struct selinux_fs_info *fsi = inode->i_sb->s_fs_info;
	struct policy_load_memory *plm = filp->private_data;

	BUG_ON(!plm);

	fsi->policy_opened = 0;

	vfree(plm->data);
	kfree(plm);

	return 0;
}
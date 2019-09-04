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
struct ovl_fs {int /*<<< orphan*/  upper_mnt; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 

void ovl_drop_write(struct dentry *dentry)
{
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;
	mnt_drop_write(ofs->upper_mnt);
}
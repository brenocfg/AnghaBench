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
typedef  int /*<<< orphan*/  umode_t ;
struct TYPE_4__ {int /*<<< orphan*/  metacopy; } ;
struct ovl_fs {TYPE_2__ config; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_3__ {struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int OPEN_FMODE (int) ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ovl_need_meta_copy_up(struct dentry *dentry, umode_t mode,
				  int flags)
{
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;

	if (!ofs->config.metacopy)
		return false;

	if (!S_ISREG(mode))
		return false;

	if (flags && ((OPEN_FMODE(flags) & FMODE_WRITE) || (flags & O_TRUNC)))
		return false;

	return true;
}
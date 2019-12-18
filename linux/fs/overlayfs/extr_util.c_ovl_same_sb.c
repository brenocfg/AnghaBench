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
struct super_block {struct ovl_fs* s_fs_info; } ;
struct ovl_fs {int numlowerfs; TYPE_2__* lower_fs; TYPE_1__* upper_mnt; } ;
struct TYPE_4__ {struct super_block* sb; } ;
struct TYPE_3__ {struct super_block* mnt_sb; } ;

/* Variables and functions */

struct super_block *ovl_same_sb(struct super_block *sb)
{
	struct ovl_fs *ofs = sb->s_fs_info;

	if (!ofs->numlowerfs)
		return ofs->upper_mnt->mnt_sb;
	else if (ofs->numlowerfs == 1 && !ofs->upper_mnt)
		return ofs->lower_fs[0].sb;
	else
		return NULL;
}
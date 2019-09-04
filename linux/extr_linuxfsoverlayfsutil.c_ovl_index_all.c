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
struct super_block {struct ovl_fs* s_fs_info; } ;
struct TYPE_2__ {scalar_t__ index; scalar_t__ nfs_export; } ;
struct ovl_fs {TYPE_1__ config; } ;

/* Variables and functions */

bool ovl_index_all(struct super_block *sb)
{
	struct ovl_fs *ofs = sb->s_fs_info;

	return ofs->config.nfs_export && ofs->config.index;
}
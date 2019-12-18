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
struct the_nilfs {struct inode* ns_dat; } ;
struct nilfs_bmap {TYPE_2__* b_inode; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */

struct inode *nilfs_bmap_get_dat(const struct nilfs_bmap *bmap)
{
	struct the_nilfs *nilfs = bmap->b_inode->i_sb->s_fs_info;

	return nilfs->ns_dat;
}
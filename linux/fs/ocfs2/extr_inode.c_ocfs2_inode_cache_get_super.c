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
struct super_block {int dummy; } ;
struct TYPE_2__ {struct super_block* i_sb; } ;
struct ocfs2_inode_info {TYPE_1__ vfs_inode; } ;
struct ocfs2_caching_info {int dummy; } ;

/* Variables and functions */
 struct ocfs2_inode_info* cache_info_to_inode (struct ocfs2_caching_info*) ; 

__attribute__((used)) static struct super_block *ocfs2_inode_cache_get_super(struct ocfs2_caching_info *ci)
{
	struct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	return oi->vfs_inode.i_sb;
}
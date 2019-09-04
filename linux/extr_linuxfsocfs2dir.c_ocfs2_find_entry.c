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
struct ocfs2_dir_lookup_result {struct ocfs2_dir_entry* dl_entry; struct buffer_head* dl_leaf_bh; } ;
struct ocfs2_dir_entry {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int ocfs2_find_entry_dx (char const*,int,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 struct buffer_head* ocfs2_find_entry_el (char const*,int,struct inode*,struct ocfs2_dir_entry**) ; 
 struct buffer_head* ocfs2_find_entry_id (char const*,int,struct inode*,struct ocfs2_dir_entry**) ; 

int ocfs2_find_entry(const char *name, int namelen,
		     struct inode *dir, struct ocfs2_dir_lookup_result *lookup)
{
	struct buffer_head *bh;
	struct ocfs2_dir_entry *res_dir = NULL;

	if (ocfs2_dir_indexed(dir))
		return ocfs2_find_entry_dx(name, namelen, dir, lookup);

	/*
	 * The unindexed dir code only uses part of the lookup
	 * structure, so there's no reason to push it down further
	 * than this.
	 */
	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		bh = ocfs2_find_entry_id(name, namelen, dir, &res_dir);
	else
		bh = ocfs2_find_entry_el(name, namelen, dir, &res_dir);

	if (bh == NULL)
		return -ENOENT;

	lookup->dl_leaf_bh = bh;
	lookup->dl_entry = res_dir;
	return 0;
}
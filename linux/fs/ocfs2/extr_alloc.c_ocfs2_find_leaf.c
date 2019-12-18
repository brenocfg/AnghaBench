#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_list {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int __ocfs2_find_path (struct ocfs2_caching_info*,struct ocfs2_extent_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  find_leaf_ins ; 
 int /*<<< orphan*/  mlog_errno (int) ; 

int ocfs2_find_leaf(struct ocfs2_caching_info *ci,
		    struct ocfs2_extent_list *root_el, u32 cpos,
		    struct buffer_head **leaf_bh)
{
	int ret;
	struct buffer_head *bh = NULL;

	ret = __ocfs2_find_path(ci, root_el, cpos, find_leaf_ins, &bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	*leaf_bh = bh;
out:
	return ret;
}
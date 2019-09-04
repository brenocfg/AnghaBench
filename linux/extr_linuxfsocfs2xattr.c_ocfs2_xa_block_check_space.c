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
struct ocfs2_xattr_info {int dummy; } ;
struct ocfs2_xa_loc {scalar_t__ xl_entry; TYPE_1__* xl_header; } ;
struct TYPE_2__ {int /*<<< orphan*/  xh_count; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_xa_can_reuse_entry (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*) ; 
 int ocfs2_xa_check_space_helper (int,int,int) ; 
 int ocfs2_xa_get_free_start (struct ocfs2_xa_loc*) ; 
 scalar_t__ ocfs2_xe_entry_usage (scalar_t__) ; 
 int ocfs2_xi_entry_usage (struct ocfs2_xattr_info*) ; 

__attribute__((used)) static int ocfs2_xa_block_check_space(struct ocfs2_xa_loc *loc,
				      struct ocfs2_xattr_info *xi)
{
	int count = le16_to_cpu(loc->xl_header->xh_count);
	int free_start = ocfs2_xa_get_free_start(loc);
	int needed_space = ocfs2_xi_entry_usage(xi);

	/*
	 * Block storage will reclaim the original entry before inserting
	 * the new value, so we only need the difference.  If the new
	 * entry is smaller than the old one, we don't need anything.
	 */
	if (loc->xl_entry) {
		/* Don't need space if we're reusing! */
		if (ocfs2_xa_can_reuse_entry(loc, xi))
			needed_space = 0;
		else
			needed_space -= ocfs2_xe_entry_usage(loc->xl_entry);
	}
	if (needed_space < 0)
		needed_space = 0;
	return ocfs2_xa_check_space_helper(needed_space, free_start, count);
}
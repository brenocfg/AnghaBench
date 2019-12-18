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
struct ocfs2_xattr_info {int dummy; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_entry; } ;

/* Variables and functions */
 scalar_t__ namevalue_size_xe (int /*<<< orphan*/ ) ; 
 scalar_t__ namevalue_size_xi (struct ocfs2_xattr_info*) ; 

__attribute__((used)) static int ocfs2_xa_block_can_reuse(struct ocfs2_xa_loc *loc,
				    struct ocfs2_xattr_info *xi)
{
	/*
	 * Block storage is strict.  If the sizes aren't exact, we will
	 * remove the old one and reinsert the new.
	 */
	return namevalue_size_xe(loc->xl_entry) ==
		namevalue_size_xi(xi);
}
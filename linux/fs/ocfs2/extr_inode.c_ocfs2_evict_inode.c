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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_2__ {int ip_flags; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_MAYBE_ORPHANED ; 
 int /*<<< orphan*/  ocfs2_clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void ocfs2_evict_inode(struct inode *inode)
{
	if (!inode->i_nlink ||
	    (OCFS2_I(inode)->ip_flags & OCFS2_INODE_MAYBE_ORPHANED)) {
		ocfs2_delete_inode(inode);
	} else {
		truncate_inode_pages_final(&inode->i_data);
	}
	ocfs2_clear_inode(inode);
}
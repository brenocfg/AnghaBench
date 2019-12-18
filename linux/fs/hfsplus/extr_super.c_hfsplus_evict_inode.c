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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct inode* rsrc_inode; } ;

/* Variables and functions */
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 int /*<<< orphan*/  INODE ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfsplus_evict_inode(struct inode *inode)
{
	hfs_dbg(INODE, "hfsplus_evict_inode: %lu\n", inode->i_ino);
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	if (HFSPLUS_IS_RSRC(inode)) {
		HFSPLUS_I(HFSPLUS_I(inode)->rsrc_inode)->rsrc_inode = NULL;
		iput(HFSPLUS_I(inode)->rsrc_inode);
	}
}
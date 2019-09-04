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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_cleanup_delete_inode (unsigned long long,int) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_cleanup_delete_inode(struct inode *inode,
				       int sync_data)
{
	trace_ocfs2_cleanup_delete_inode(
		(unsigned long long)OCFS2_I(inode)->ip_blkno, sync_data);
	if (sync_data)
		filemap_write_and_wait(inode->i_mapping);
	truncate_inode_pages_final(&inode->i_data);
}
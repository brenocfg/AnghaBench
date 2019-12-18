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
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int sync_inode_metadata (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int writeback_inode(struct inode *inode)
{

	int ret;

	/* if we used wait=1, sync_inode_metadata waits for the io for the
	* inode to finish.  So wait=0 is sent down to sync_inode_metadata
	* and filemap_fdatawrite is used for the data blocks
	*/
	ret = sync_inode_metadata(inode, 0);
	if (!ret)
		ret = filemap_fdatawrite(inode->i_mapping);
	return ret;
}
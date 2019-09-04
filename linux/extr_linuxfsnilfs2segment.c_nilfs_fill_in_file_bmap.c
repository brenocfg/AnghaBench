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
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;
struct nilfs_inode_info {TYPE_1__ vfs_inode; int /*<<< orphan*/  i_bmap; struct buffer_head* i_bh; int /*<<< orphan*/  i_state; } ;
struct nilfs_inode {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NILFS_I_BMAP ; 
 int /*<<< orphan*/  nilfs_bmap_write (int /*<<< orphan*/ ,struct nilfs_inode*) ; 
 struct nilfs_inode* nilfs_ifile_map_inode (struct inode*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_ifile_unmap_inode (struct inode*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_fill_in_file_bmap(struct inode *ifile,
				    struct nilfs_inode_info *ii)

{
	struct buffer_head *ibh;
	struct nilfs_inode *raw_inode;

	if (test_bit(NILFS_I_BMAP, &ii->i_state)) {
		ibh = ii->i_bh;
		BUG_ON(!ibh);
		raw_inode = nilfs_ifile_map_inode(ifile, ii->vfs_inode.i_ino,
						  ibh);
		nilfs_bmap_write(ii->i_bmap, raw_inode);
		nilfs_ifile_unmap_inode(ifile, ii->vfs_inode.i_ino, ibh);
	}
}
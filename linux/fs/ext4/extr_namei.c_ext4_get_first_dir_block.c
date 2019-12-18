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
struct inode {TYPE_1__* i_sb; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRENT_HTREE ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 struct buffer_head* ext4_get_first_inline_block (struct inode*,struct ext4_dir_entry_2**,int*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,int /*<<< orphan*/ ) ; 
 struct buffer_head* ext4_read_dirblock (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer_head *ext4_get_first_dir_block(handle_t *handle,
					struct inode *inode,
					int *retval,
					struct ext4_dir_entry_2 **parent_de,
					int *inlined)
{
	struct buffer_head *bh;

	if (!ext4_has_inline_data(inode)) {
		/* The first directory block must not be a hole, so
		 * treat it as DIRENT_HTREE
		 */
		bh = ext4_read_dirblock(inode, 0, DIRENT_HTREE);
		if (IS_ERR(bh)) {
			*retval = PTR_ERR(bh);
			return NULL;
		}
		*parent_de = ext4_next_entry(
					(struct ext4_dir_entry_2 *)bh->b_data,
					inode->i_sb->s_blocksize);
		return bh;
	}

	*inlined = 1;
	return ext4_get_first_inline_block(inode, parent_de, retval);
}
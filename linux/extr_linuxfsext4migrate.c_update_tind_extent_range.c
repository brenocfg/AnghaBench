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
struct migrate_struct {unsigned long curr_block; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 struct buffer_head* ext4_sb_bread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int update_dind_extent_range (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,struct migrate_struct*) ; 

__attribute__((used)) static int update_tind_extent_range(handle_t *handle, struct inode *inode,
				    ext4_fsblk_t pblock,
				    struct migrate_struct *lb)
{
	struct buffer_head *bh;
	__le32 *i_data;
	int i, retval = 0;
	unsigned long max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bread(inode->i_sb, pblock, 0);
	if (IS_ERR(bh))
		return PTR_ERR(bh);

	i_data = (__le32 *)bh->b_data;
	for (i = 0; i < max_entries; i++) {
		if (i_data[i]) {
			retval = update_dind_extent_range(handle, inode,
						le32_to_cpu(i_data[i]), lb);
			if (retval)
				break;
		} else {
			/* Only update the file block number */
			lb->curr_block += max_entries * max_entries;
		}
	}
	put_bh(bh);
	return retval;

}
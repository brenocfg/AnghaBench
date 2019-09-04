#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext4_allocation_request {int flags; int len; TYPE_2__* inode; int /*<<< orphan*/  goal; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_8__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {struct buffer_head* bh; int /*<<< orphan*/ * p; void* key; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int ENOMEM ; 
 int EXT4_MB_DELALLOC_RESERVED ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_forget (int /*<<< orphan*/ *,int,TYPE_2__*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,TYPE_2__*,struct buffer_head*) ; 
 int ext4_journal_get_create_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mb_new_blocks (int /*<<< orphan*/ *,struct ext4_allocation_request*,int*) ; 
 int /*<<< orphan*/  ext4_new_meta_blocks (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext4_alloc_branch(handle_t *handle,
			     struct ext4_allocation_request *ar,
			     int indirect_blks, ext4_lblk_t *offsets,
			     Indirect *branch)
{
	struct buffer_head *		bh;
	ext4_fsblk_t			b, new_blocks[4];
	__le32				*p;
	int				i, j, err, len = 1;

	for (i = 0; i <= indirect_blks; i++) {
		if (i == indirect_blks) {
			new_blocks[i] = ext4_mb_new_blocks(handle, ar, &err);
		} else
			ar->goal = new_blocks[i] = ext4_new_meta_blocks(handle,
					ar->inode, ar->goal,
					ar->flags & EXT4_MB_DELALLOC_RESERVED,
					NULL, &err);
		if (err) {
			i--;
			goto failed;
		}
		branch[i].key = cpu_to_le32(new_blocks[i]);
		if (i == 0)
			continue;

		bh = branch[i].bh = sb_getblk(ar->inode->i_sb, new_blocks[i-1]);
		if (unlikely(!bh)) {
			err = -ENOMEM;
			goto failed;
		}
		lock_buffer(bh);
		BUFFER_TRACE(bh, "call get_create_access");
		err = ext4_journal_get_create_access(handle, bh);
		if (err) {
			unlock_buffer(bh);
			goto failed;
		}

		memset(bh->b_data, 0, bh->b_size);
		p = branch[i].p = (__le32 *) bh->b_data + offsets[i];
		b = new_blocks[i];

		if (i == indirect_blks)
			len = ar->len;
		for (j = 0; j < len; j++)
			*p++ = cpu_to_le32(b++);

		BUFFER_TRACE(bh, "marking uptodate");
		set_buffer_uptodate(bh);
		unlock_buffer(bh);

		BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, ar->inode, bh);
		if (err)
			goto failed;
	}
	return 0;
failed:
	for (; i >= 0; i--) {
		/*
		 * We want to ext4_forget() only freshly allocated indirect
		 * blocks.  Buffer for new_blocks[i-1] is at branch[i].bh and
		 * buffer at branch[0].bh is indirect block / inode already
		 * existing before ext4_alloc_branch() was called.
		 */
		if (i > 0 && i != indirect_blks && branch[i].bh)
			ext4_forget(handle, 1, ar->inode, branch[i].bh,
				    branch[i].bh->b_blocknr);
		ext4_free_blocks(handle, ar->inode, NULL, new_blocks[i],
				 (i == indirect_blks) ? ar->len : 1, 0);
	}
	return err;
}
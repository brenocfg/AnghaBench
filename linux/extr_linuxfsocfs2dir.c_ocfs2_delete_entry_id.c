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
struct ocfs2_inline_data {int /*<<< orphan*/  id_data; } ;
struct ocfs2_dir_entry {int dummy; } ;
struct TYPE_2__ {struct ocfs2_inline_data i_data; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static inline int ocfs2_delete_entry_id(handle_t *handle,
					struct inode *dir,
					struct ocfs2_dir_entry *de_del,
					struct buffer_head *bh)
{
	int ret;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_inline_data *data;

	ret = ocfs2_read_inode_block(dir, &di_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	ret = __ocfs2_delete_entry(handle, dir, de_del, bh, data->id_data,
				   i_size_read(dir));

	brelse(di_bh);
out:
	return ret;
}
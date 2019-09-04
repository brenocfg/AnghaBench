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

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int ocfs2_search_dirblock (struct buffer_head*,struct inode*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_entry**) ; 

__attribute__((used)) static struct buffer_head *ocfs2_find_entry_id(const char *name,
					       int namelen,
					       struct inode *dir,
					       struct ocfs2_dir_entry **res_dir)
{
	int ret, found;
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

	found = ocfs2_search_dirblock(di_bh, dir, name, namelen, 0,
				      data->id_data, i_size_read(dir), res_dir);
	if (found == 1)
		return di_bh;

	brelse(di_bh);
out:
	return NULL;
}
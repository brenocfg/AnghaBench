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
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; scalar_t__ inode; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int (* ocfs2_journal_access_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,int) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int __ocfs2_delete_entry(handle_t *handle, struct inode *dir,
				struct ocfs2_dir_entry *de_del,
				struct buffer_head *bh, char *first_de,
				unsigned int bytes)
{
	struct ocfs2_dir_entry *de, *pde;
	int i, status = -ENOENT;
	ocfs2_journal_access_func access = ocfs2_journal_access_db;

	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		access = ocfs2_journal_access_di;

	i = 0;
	pde = NULL;
	de = (struct ocfs2_dir_entry *) first_de;
	while (i < bytes) {
		if (!ocfs2_check_dir_entry(dir, de, bh, i)) {
			status = -EIO;
			mlog_errno(status);
			goto bail;
		}
		if (de == de_del)  {
			status = access(handle, INODE_CACHE(dir), bh,
					OCFS2_JOURNAL_ACCESS_WRITE);
			if (status < 0) {
				status = -EIO;
				mlog_errno(status);
				goto bail;
			}
			if (pde)
				le16_add_cpu(&pde->rec_len,
						le16_to_cpu(de->rec_len));
			de->inode = 0;
			inode_inc_iversion(dir);
			ocfs2_journal_dirty(handle, bh);
			goto bail;
		}
		i += le16_to_cpu(de->rec_len);
		pde = de;
		de = (struct ocfs2_dir_entry *)((char *)de + le16_to_cpu(de->rec_len));
	}
bail:
	return status;
}
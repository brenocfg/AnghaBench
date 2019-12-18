#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; scalar_t__ inode; scalar_t__ name_len; } ;
struct TYPE_3__ {char* id_data; } ;
struct TYPE_4__ {TYPE_1__ i_data; } ;
struct ocfs2_dinode {TYPE_2__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_dx_entries_per_root (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_new_dx_should_be_inline(struct inode *dir,
					 struct buffer_head *di_bh)
{
	int dirent_count = 0;
	char *de_buf, *limit;
	struct ocfs2_dir_entry *de;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;

	de_buf = di->id2.i_data.id_data;
	limit = de_buf + i_size_read(dir);

	while (de_buf < limit) {
		de = (struct ocfs2_dir_entry *)de_buf;

		if (de->name_len && de->inode)
			dirent_count++;

		de_buf += le16_to_cpu(de->rec_len);
	}

	/* We are careful to leave room for one extra record. */
	return dirent_count < ocfs2_dx_entries_per_root(dir->i_sb);
}
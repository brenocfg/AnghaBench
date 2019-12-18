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
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {int name_len; int /*<<< orphan*/  rec_len; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ext4_check_dir_entry (struct inode*,int /*<<< orphan*/ *,struct ext4_dir_entry_2*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ext4_match (struct inode*,struct ext4_filename*,struct ext4_dir_entry_2*) ; 
 int ext4_rec_len_from_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ext4_search_dir(struct buffer_head *bh, char *search_buf, int buf_size,
		    struct inode *dir, struct ext4_filename *fname,
		    unsigned int offset, struct ext4_dir_entry_2 **res_dir)
{
	struct ext4_dir_entry_2 * de;
	char * dlimit;
	int de_len;

	de = (struct ext4_dir_entry_2 *)search_buf;
	dlimit = search_buf + buf_size;
	while ((char *) de < dlimit) {
		/* this code is executed quadratically often */
		/* do minimal checking `by hand' */
		if ((char *) de + de->name_len <= dlimit &&
		    ext4_match(dir, fname, de)) {
			/* found a match - just to be sure, do
			 * a full check */
			if (ext4_check_dir_entry(dir, NULL, de, bh, bh->b_data,
						 bh->b_size, offset))
				return -1;
			*res_dir = de;
			return 1;
		}
		/* prevent looping on a bad block */
		de_len = ext4_rec_len_from_disk(de->rec_len,
						dir->i_sb->s_blocksize);
		if (de_len <= 0)
			return -1;
		offset += de_len;
		de = (struct ext4_dir_entry_2 *) ((char *) de + de_len);
	}
	return 0;
}
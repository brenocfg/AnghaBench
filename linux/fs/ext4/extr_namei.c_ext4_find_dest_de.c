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
struct inode {int dummy; } ;
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {scalar_t__ inode; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  name_len; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFSCORRUPTED ; 
 int ENOSPC ; 
 void* EXT4_DIR_REC_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_check_dir_entry (struct inode*,int /*<<< orphan*/ *,struct ext4_dir_entry_2*,struct buffer_head*,void*,int,unsigned int) ; 
 scalar_t__ ext4_match (struct inode*,struct ext4_filename*,struct ext4_dir_entry_2*) ; 
 int ext4_rec_len_from_disk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fname_len (struct ext4_filename*) ; 

int ext4_find_dest_de(struct inode *dir, struct inode *inode,
		      struct buffer_head *bh,
		      void *buf, int buf_size,
		      struct ext4_filename *fname,
		      struct ext4_dir_entry_2 **dest_de)
{
	struct ext4_dir_entry_2 *de;
	unsigned short reclen = EXT4_DIR_REC_LEN(fname_len(fname));
	int nlen, rlen;
	unsigned int offset = 0;
	char *top;

	de = (struct ext4_dir_entry_2 *)buf;
	top = buf + buf_size - reclen;
	while ((char *) de <= top) {
		if (ext4_check_dir_entry(dir, NULL, de, bh,
					 buf, buf_size, offset))
			return -EFSCORRUPTED;
		if (ext4_match(dir, fname, de))
			return -EEXIST;
		nlen = EXT4_DIR_REC_LEN(de->name_len);
		rlen = ext4_rec_len_from_disk(de->rec_len, buf_size);
		if ((de->inode ? rlen - nlen : rlen) >= reclen)
			break;
		de = (struct ext4_dir_entry_2 *)((char *)de + rlen);
		offset += rlen;
	}
	if ((char *) de > top)
		return -ENOSPC;

	*dest_de = de;
	return 0;
}
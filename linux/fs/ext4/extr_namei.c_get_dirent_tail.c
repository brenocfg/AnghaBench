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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_dir_entry_tail {scalar_t__ det_reserved_ft; scalar_t__ det_reserved_zero2; scalar_t__ det_rec_len; scalar_t__ det_reserved_zero1; } ;
struct ext4_dir_entry {scalar_t__ rec_len; } ;
struct buffer_head {int b_data; } ;

/* Variables and functions */
 int EXT4_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 struct ext4_dir_entry_tail* EXT4_DIRENT_TAIL (int,int) ; 
 scalar_t__ EXT4_FT_DIR_CSUM ; 
 int le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static struct ext4_dir_entry_tail *get_dirent_tail(struct inode *inode,
						   struct buffer_head *bh)
{
	struct ext4_dir_entry_tail *t;

#ifdef PARANOID
	struct ext4_dir_entry *d, *top;

	d = (struct ext4_dir_entry *)bh->b_data;
	top = (struct ext4_dir_entry *)(bh->b_data +
		(EXT4_BLOCK_SIZE(inode->i_sb) -
		 sizeof(struct ext4_dir_entry_tail)));
	while (d < top && d->rec_len)
		d = (struct ext4_dir_entry *)(((void *)d) +
		    le16_to_cpu(d->rec_len));

	if (d != top)
		return NULL;

	t = (struct ext4_dir_entry_tail *)d;
#else
	t = EXT4_DIRENT_TAIL(bh->b_data, EXT4_BLOCK_SIZE(inode->i_sb));
#endif

	if (t->det_reserved_zero1 ||
	    le16_to_cpu(t->det_rec_len) != sizeof(struct ext4_dir_entry_tail) ||
	    t->det_reserved_zero2 ||
	    t->det_reserved_ft != EXT4_FT_DIR_CSUM)
		return NULL;

	return t;
}
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
struct ext4_dir_entry_tail {int /*<<< orphan*/  det_reserved_ft; int /*<<< orphan*/  det_rec_len; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 struct ext4_dir_entry_tail* EXT4_DIRENT_TAIL (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  EXT4_FT_DIR_CSUM ; 
 int /*<<< orphan*/  ext4_rec_len_to_disk (int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ext4_dir_entry_tail*,int /*<<< orphan*/ ,int) ; 

void ext4_initialize_dirent_tail(struct buffer_head *bh,
				 unsigned int blocksize)
{
	struct ext4_dir_entry_tail *t = EXT4_DIRENT_TAIL(bh->b_data, blocksize);

	memset(t, 0, sizeof(struct ext4_dir_entry_tail));
	t->det_rec_len = ext4_rec_len_to_disk(
			sizeof(struct ext4_dir_entry_tail), blocksize);
	t->det_reserved_ft = EXT4_FT_DIR_CSUM;
}
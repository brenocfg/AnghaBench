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
struct inode {unsigned int i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext4_dir_entry_2 {int name_len; int /*<<< orphan*/  name; void* rec_len; void* inode; } ;

/* Variables and functions */
 scalar_t__ EXT4_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 void* cpu_to_le32 (unsigned int) ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,int) ; 
 void* ext4_rec_len_to_disk (scalar_t__,int) ; 
 int /*<<< orphan*/  ext4_set_de_type (int /*<<< orphan*/ ,struct ext4_dir_entry_2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

struct ext4_dir_entry_2 *ext4_init_dot_dotdot(struct inode *inode,
			  struct ext4_dir_entry_2 *de,
			  int blocksize, int csum_size,
			  unsigned int parent_ino, int dotdot_real_len)
{
	de->inode = cpu_to_le32(inode->i_ino);
	de->name_len = 1;
	de->rec_len = ext4_rec_len_to_disk(EXT4_DIR_REC_LEN(de->name_len),
					   blocksize);
	strcpy(de->name, ".");
	ext4_set_de_type(inode->i_sb, de, S_IFDIR);

	de = ext4_next_entry(de, blocksize);
	de->inode = cpu_to_le32(parent_ino);
	de->name_len = 2;
	if (!dotdot_real_len)
		de->rec_len = ext4_rec_len_to_disk(blocksize -
					(csum_size + EXT4_DIR_REC_LEN(1)),
					blocksize);
	else
		de->rec_len = ext4_rec_len_to_disk(
				EXT4_DIR_REC_LEN(de->name_len), blocksize);
	strcpy(de->name, "..");
	ext4_set_de_type(inode->i_sb, de, S_IFDIR);

	return ext4_next_entry(de, blocksize);
}
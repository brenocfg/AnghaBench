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
struct ext4_dir_entry_tail {int /*<<< orphan*/  det_checksum; } ;
struct ext4_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_dirent_csum (struct inode*,struct ext4_dir_entry*,int) ; 
 int /*<<< orphan*/  ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 
 struct ext4_dir_entry_tail* get_dirent_tail (struct inode*,struct ext4_dir_entry*) ; 
 int /*<<< orphan*/  warn_no_space_for_csum (struct inode*) ; 

__attribute__((used)) static void ext4_dirent_csum_set(struct inode *inode,
				 struct ext4_dir_entry *dirent)
{
	struct ext4_dir_entry_tail *t;

	if (!ext4_has_metadata_csum(inode->i_sb))
		return;

	t = get_dirent_tail(inode, dirent);
	if (!t) {
		warn_no_space_for_csum(inode);
		return;
	}

	t->det_checksum = ext4_dirent_csum(inode, dirent,
					   (void *)t - (void *)dirent);
}
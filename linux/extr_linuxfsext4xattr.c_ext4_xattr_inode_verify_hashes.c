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
typedef  scalar_t__ u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_xattr_entry {scalar_t__ e_hash; int /*<<< orphan*/  e_name_len; int /*<<< orphan*/  e_name; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 scalar_t__ ext4_xattr_hash_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ ext4_xattr_inode_get_hash (struct inode*) ; 
 scalar_t__ ext4_xattr_inode_hash (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
ext4_xattr_inode_verify_hashes(struct inode *ea_inode,
			       struct ext4_xattr_entry *entry, void *buffer,
			       size_t size)
{
	u32 hash;

	/* Verify stored hash matches calculated hash. */
	hash = ext4_xattr_inode_hash(EXT4_SB(ea_inode->i_sb), buffer, size);
	if (hash != ext4_xattr_inode_get_hash(ea_inode))
		return -EFSCORRUPTED;

	if (entry) {
		__le32 e_hash, tmp_data;

		/* Verify entry hash. */
		tmp_data = cpu_to_le32(hash);
		e_hash = ext4_xattr_hash_entry(entry->e_name, entry->e_name_len,
					       &tmp_data, 1);
		if (e_hash != entry->e_hash)
			return -EFSCORRUPTED;
	}
	return 0;
}
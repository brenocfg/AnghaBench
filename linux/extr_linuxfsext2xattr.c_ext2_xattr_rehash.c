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
struct ext2_xattr_header {int /*<<< orphan*/  h_hash; } ;
struct ext2_xattr_entry {int /*<<< orphan*/  e_hash; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int __u32 ;

/* Variables and functions */
 int BLOCK_HASH_SHIFT ; 
 struct ext2_xattr_entry* ENTRY (struct ext2_xattr_header*) ; 
 struct ext2_xattr_entry* EXT2_XATTR_NEXT (struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ext2_xattr_hash_entry (struct ext2_xattr_header*,struct ext2_xattr_entry*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext2_xattr_rehash(struct ext2_xattr_header *header,
			      struct ext2_xattr_entry *entry)
{
	struct ext2_xattr_entry *here;
	__u32 hash = 0;
	
	ext2_xattr_hash_entry(header, entry);
	here = ENTRY(header+1);
	while (!IS_LAST_ENTRY(here)) {
		if (!here->e_hash) {
			/* Block is not shared if an entry's hash value == 0 */
			hash = 0;
			break;
		}
		hash = (hash << BLOCK_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - BLOCK_HASH_SHIFT)) ^
		       le32_to_cpu(here->e_hash);
		here = EXT2_XATTR_NEXT(here);
	}
	header->h_hash = cpu_to_le32(hash);
}
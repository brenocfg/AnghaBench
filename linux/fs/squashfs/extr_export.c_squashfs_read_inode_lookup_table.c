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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 unsigned int SQUASHFS_LOOKUP_BLOCK_BYTES (unsigned int) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * squashfs_read_table (struct super_block*,scalar_t__,unsigned int) ; 

__le64 *squashfs_read_inode_lookup_table(struct super_block *sb,
		u64 lookup_table_start, u64 next_table, unsigned int inodes)
{
	unsigned int length = SQUASHFS_LOOKUP_BLOCK_BYTES(inodes);
	__le64 *table;

	TRACE("In read_inode_lookup_table, length %d\n", length);

	/* Sanity check values */

	/* there should always be at least one inode */
	if (inodes == 0)
		return ERR_PTR(-EINVAL);

	/* length bytes should not extend into the next table - this check
	 * also traps instances where lookup_table_start is incorrectly larger
	 * than the next table start
	 */
	if (lookup_table_start + length > next_table)
		return ERR_PTR(-EINVAL);

	table = squashfs_read_table(sb, lookup_table_start, length);

	/*
	 * table[0] points to the first inode lookup table metadata block,
	 * this should be less than lookup_table_start
	 */
	if (!IS_ERR(table) && le64_to_cpu(table[0]) >= lookup_table_start) {
		kfree(table);
		return ERR_PTR(-EINVAL);
	}

	return table;
}
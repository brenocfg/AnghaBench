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
struct squashfs_xattr_id_table {int /*<<< orphan*/  xattr_ids; int /*<<< orphan*/  xattr_table_start; } ;
typedef  struct squashfs_xattr_id_table __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct squashfs_xattr_id_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct squashfs_xattr_id_table*) ; 
 unsigned int SQUASHFS_XATTR_BLOCK_BYTES (int) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct squashfs_xattr_id_table*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct squashfs_xattr_id_table* squashfs_read_table (struct super_block*,scalar_t__,unsigned int) ; 

__le64 *squashfs_read_xattr_id_table(struct super_block *sb, u64 start,
		u64 *xattr_table_start, int *xattr_ids)
{
	unsigned int len;
	struct squashfs_xattr_id_table *id_table;

	id_table = squashfs_read_table(sb, start, sizeof(*id_table));
	if (IS_ERR(id_table))
		return (__le64 *) id_table;

	*xattr_table_start = le64_to_cpu(id_table->xattr_table_start);
	*xattr_ids = le32_to_cpu(id_table->xattr_ids);
	kfree(id_table);

	/* Sanity check values */

	/* there is always at least one xattr id */
	if (*xattr_ids == 0)
		return ERR_PTR(-EINVAL);

	/* xattr_table should be less than start */
	if (*xattr_table_start >= start)
		return ERR_PTR(-EINVAL);

	len = SQUASHFS_XATTR_BLOCK_BYTES(*xattr_ids);

	TRACE("In read_xattr_index_table, length %d\n", len);

	return squashfs_read_table(sb, start + sizeof(*id_table), len);
}
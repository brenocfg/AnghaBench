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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le64 *squashfs_read_xattr_id_table(struct super_block *sb,
		u64 start, u64 *xattr_table_start, int *xattr_ids)
{
	ERROR("Xattrs in filesystem, these will be ignored\n");
	*xattr_table_start = start;
	return ERR_PTR(-ENOTSUPP);
}
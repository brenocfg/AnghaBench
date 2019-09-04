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
struct z_erofs_vle_decompressed_index {int dummy; } ;
struct erofs_xattr_ibody_header {int dummy; } ;
struct erofs_xattr_entry {int dummy; } ;
struct erofs_super_block {int dummy; } ;
struct erofs_inode_v2 {int dummy; } ;
struct erofs_inode_v1 {int dummy; } ;
struct erofs_extent_header {int dummy; } ;
struct erofs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline void erofs_check_ondisk_layout_definitions(void)
{
	BUILD_BUG_ON(sizeof(struct erofs_super_block) != 128);
	BUILD_BUG_ON(sizeof(struct erofs_inode_v1) != 32);
	BUILD_BUG_ON(sizeof(struct erofs_inode_v2) != 64);
	BUILD_BUG_ON(sizeof(struct erofs_xattr_ibody_header) != 12);
	BUILD_BUG_ON(sizeof(struct erofs_xattr_entry) != 4);
	BUILD_BUG_ON(sizeof(struct erofs_extent_header) != 16);
	BUILD_BUG_ON(sizeof(struct z_erofs_vle_decompressed_index) != 8);
	BUILD_BUG_ON(sizeof(struct erofs_dirent) != 12);
}
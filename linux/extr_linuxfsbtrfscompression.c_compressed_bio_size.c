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
typedef  int u16 ;
struct compressed_bio {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  super_copy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int btrfs_super_csum_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int compressed_bio_size(struct btrfs_fs_info *fs_info,
				      unsigned long disk_size)
{
	u16 csum_size = btrfs_super_csum_size(fs_info->super_copy);

	return sizeof(struct compressed_bio) +
		(DIV_ROUND_UP(disk_size, fs_info->sectorsize)) * csum_size;
}
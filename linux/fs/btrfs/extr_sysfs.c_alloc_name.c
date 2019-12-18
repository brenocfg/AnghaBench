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
typedef  int u64 ;

/* Variables and functions */
#define  BTRFS_BLOCK_GROUP_DATA 130 
#define  BTRFS_BLOCK_GROUP_METADATA 129 
#define  BTRFS_BLOCK_GROUP_SYSTEM 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static const char *alloc_name(u64 flags)
{
	switch (flags) {
	case BTRFS_BLOCK_GROUP_METADATA | BTRFS_BLOCK_GROUP_DATA:
		return "mixed";
	case BTRFS_BLOCK_GROUP_METADATA:
		return "metadata";
	case BTRFS_BLOCK_GROUP_DATA:
		return "data";
	case BTRFS_BLOCK_GROUP_SYSTEM:
		return "system";
	default:
		WARN_ON(1);
		return "invalid-combination";
	};
}
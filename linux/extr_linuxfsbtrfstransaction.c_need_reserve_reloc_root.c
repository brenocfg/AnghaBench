#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {scalar_t__ reloc_root; TYPE_1__ root_key; int /*<<< orphan*/  state; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  reloc_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_REF_COWS ; 
 scalar_t__ BTRFS_TREE_RELOC_OBJECTID ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool need_reserve_reloc_root(struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (!fs_info->reloc_ctl ||
	    !test_bit(BTRFS_ROOT_REF_COWS, &root->state) ||
	    root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID ||
	    root->reloc_root)
		return false;

	return true;
}
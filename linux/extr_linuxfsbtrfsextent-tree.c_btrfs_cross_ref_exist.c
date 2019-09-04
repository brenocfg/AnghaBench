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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; } ;
struct btrfs_path {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_DATA_RELOC_TREE_OBJECTID ; 
 int EAGAIN ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int check_committed_ref (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_delayed_ref (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_cross_ref_exist(struct btrfs_root *root, u64 objectid, u64 offset,
			  u64 bytenr)
{
	struct btrfs_path *path;
	int ret;
	int ret2;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	do {
		ret = check_committed_ref(root, path, objectid,
					  offset, bytenr);
		if (ret && ret != -ENOENT)
			goto out;

		ret2 = check_delayed_ref(root, path, objectid,
					 offset, bytenr);
	} while (ret2 == -EAGAIN);

	if (ret2 && ret2 != -ENOENT) {
		ret = ret2;
		goto out;
	}

	if (ret != -ENOENT || ret2 != -ENOENT)
		ret = 0;
out:
	btrfs_free_path(path);
	if (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID)
		WARN_ON(ret > 0);
	return ret;
}
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
struct btrfs_root_item {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_inode_ref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_REF_KEY ; 
 scalar_t__ BtrFsSearchTreeType (struct btrfs_root_item const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_path*) ; 
 int /*<<< orphan*/  INVALID_INODE ; 
 int /*<<< orphan*/  free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  init_path (struct btrfs_path*) ; 
 scalar_t__ path_current_data (struct btrfs_path*) ; 
 TYPE_1__* path_current_disk_key (struct btrfs_path*) ; 

__attribute__((used)) static u64 btrfs_lookup_inode_ref(const struct btrfs_root_item *root, u64 inr,
                                  struct btrfs_inode_ref *refp, char *name)
{
    struct btrfs_path path;
    struct btrfs_inode_ref *ref;
    u64 ret = INVALID_INODE;
    init_path(&path);

    if (BtrFsSearchTreeType(root, inr, BTRFS_INODE_REF_KEY, &path))
    {
        ref = (struct btrfs_inode_ref *) path_current_data(&path);

        if (refp)
            *refp = *ref;
        ret = path_current_disk_key(&path)->offset;
    }

    free_path(&path);
    return ret;
}
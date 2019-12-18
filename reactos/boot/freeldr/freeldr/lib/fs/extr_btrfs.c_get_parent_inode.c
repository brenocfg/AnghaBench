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
struct btrfs_root_item {int dummy; } ;
struct btrfs_inode_item {int dummy; } ;
struct btrfs_disk_key {scalar_t__ offset; void* type; scalar_t__ objectid; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 void* BTRFS_INODE_ITEM_KEY ; 
 scalar_t__ INVALID_INODE ; 
 scalar_t__ btrfs_lookup_inode (struct btrfs_root_item const*,struct btrfs_disk_key*,struct btrfs_inode_item*,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_lookup_inode_ref (struct btrfs_root_item const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 get_parent_inode(const struct btrfs_root_item *root, u64 inr,
                            struct btrfs_inode_item *inode_item)
{
    struct btrfs_disk_key key;
    u64 res;

    if (inr == BTRFS_FIRST_FREE_OBJECTID)
    {
//        if (root->objectid != btrfs_info.fs_root.objectid) {
//            u64 parent;
//            struct btrfs_root_ref ref;
//
//            parent = btrfs_lookup_root_ref(root->objectid, &ref,
//                                           NULL);
//            if (parent == -1ULL)
//                return -1ULL;
//
//            if (btrfs_find_root(parent, root, NULL))
//                return -1ULL;
//
//            inr = ref.dirid;
//        }

        if (inode_item)
        {
            key.objectid = inr;
            key.type = BTRFS_INODE_ITEM_KEY;
            key.offset = 0;

            if (btrfs_lookup_inode(root, &key, inode_item, NULL))
                return INVALID_INODE;
        }

        return inr;
    }

    res = btrfs_lookup_inode_ref(root, inr, NULL, NULL);
    if (res == INVALID_INODE)
        return INVALID_INODE;

    if (inode_item)
    {
        key.objectid = res;
        key.type = BTRFS_INODE_ITEM_KEY;
        key.offset = 0;

        if (btrfs_lookup_inode(root, &key, inode_item, NULL))
            return INVALID_INODE;
    }

    return res;
}
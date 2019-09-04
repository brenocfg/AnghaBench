#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btrfs_path {int* itemsnr; int* slots; scalar_t__* offsets; } ;
struct btrfs_disk_key {int dummy; } ;
struct TYPE_3__ {scalar_t__ objectid; } ;

/* Variables and functions */
 int BTRFS_MAX_LEVEL ; 
 int /*<<< orphan*/  _BtrFsSearchTree (scalar_t__,int,struct btrfs_disk_key*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_comp_keys_type (struct btrfs_disk_key*,TYPE_1__*) ; 
 TYPE_1__* path_current_disk_key (struct btrfs_path*) ; 

__attribute__((used)) static int next_slot(struct btrfs_disk_key *key,
                     struct btrfs_path *path)
{
    int slot, level = 1;

    if (!path->itemsnr[0])
        return 1;
    slot = path->slots[0] + 1;
    if (slot >= path->itemsnr[0])
    {
        /* jumping to next leaf */
        while (level < BTRFS_MAX_LEVEL)
        {
            if (!path->itemsnr[level]) /* no more nodes */
                return 1;
            slot = path->slots[level] + 1;
            if (slot >= path->itemsnr[level])
            {
                level++;
                continue;;
            }
            path->slots[level] = slot;
            path->slots[level - 1] = 0; /* reset low level slots info */
            path->itemsnr[level - 1] = 0;
            path->offsets[level - 1] = 0;
            _BtrFsSearchTree(path->offsets[level], level, key, path);
            break;
        }
        if (level == BTRFS_MAX_LEVEL)
            return 1;
        goto out;
    }
    path->slots[0] = slot;

out:
    if (path_current_disk_key(path)->objectid && !btrfs_comp_keys_type(key, path_current_disk_key(path)))
        return 0;
    else
        return 1;
}
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
struct btrfs_root_item {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_disk_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_dir_item {int dummy; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DIR_ITEM_KEY ; 
 struct btrfs_dir_item* BtrFsMatchDirItemName (struct btrfs_path*,char const*,int) ; 
 int /*<<< orphan*/  BtrFsSearchTree (struct btrfs_root_item const*,struct btrfs_disk_key*,struct btrfs_path*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  btrfs_crc32c (char const*,int) ; 
 int /*<<< orphan*/  free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  init_path (struct btrfs_path*) ; 

__attribute__((used)) static BOOLEAN BtrFsLookupDirItem(const struct btrfs_root_item *root, u64 dir, const char *name, int name_len,
                                  struct btrfs_dir_item *item)
{
    struct btrfs_path path;
    struct btrfs_disk_key key;
    struct btrfs_dir_item *res = NULL;

    key.objectid = dir;
    key.type = BTRFS_DIR_ITEM_KEY;
    key.offset = btrfs_crc32c(name, name_len);
    init_path(&path);

    if (!BtrFsSearchTree(root, &key, &path))
    {
        free_path(&path);
        return FALSE;
    }

    res = BtrFsMatchDirItemName(&path, name, name_len);
    if (res)
        *item = *res;
    free_path(&path);

    return res != NULL;
}
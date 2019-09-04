#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_root_item {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_file_extent_item {scalar_t__ type; } ;
struct btrfs_disk_key {scalar_t__ offset; int /*<<< orphan*/  type; scalar_t__ objectid; } ;
struct TYPE_4__ {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EXTENT_DATA_KEY ; 
 scalar_t__ BTRFS_FILE_EXTENT_INLINE ; 
 int /*<<< orphan*/  BtrFsSearchTree (struct btrfs_root_item const*,struct btrfs_disk_key*,struct btrfs_path*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ READ_ERROR ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ btrfs_comp_keys (struct btrfs_disk_key*,TYPE_1__*) ; 
 scalar_t__ btrfs_comp_keys_type (struct btrfs_disk_key*,TYPE_1__*) ; 
 scalar_t__ btrfs_read_extent_inline (struct btrfs_path*,struct btrfs_file_extent_item*,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ btrfs_read_extent_reg (struct btrfs_path*,struct btrfs_file_extent_item*,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  init_path (struct btrfs_path*) ; 
 int next_slot (struct btrfs_disk_key*,struct btrfs_path*) ; 
 scalar_t__ path_current_data (struct btrfs_path*) ; 
 TYPE_1__* path_current_disk_key (struct btrfs_path*) ; 
 scalar_t__ prev_slot (struct btrfs_disk_key*,struct btrfs_path*) ; 

__attribute__((used)) static u64 btrfs_file_read(const struct btrfs_root_item *root, u64 inr, u64 offset, u64 size, char *buf)
{
    struct btrfs_path path;
    struct btrfs_disk_key key;
    struct btrfs_file_extent_item *extent;
    int res = 0;
    u64 rd, seek_pointer = READ_ERROR, offset_in_extent;
    BOOLEAN find_res;

    TRACE("btrfs_file_read inr=%llu offset=%llu size=%llu\n", inr, offset, size);

    key.objectid = inr;
    key.type = BTRFS_EXTENT_DATA_KEY;
    key.offset = offset;
    init_path(&path);

    find_res = BtrFsSearchTree(root, &key, &path);

    /* if we found greater key, switch to the previous one */
    if (!find_res && btrfs_comp_keys(&key, path_current_disk_key(&path)) < 0)
    {
        if (prev_slot(&key, &path))
            goto out;

    } else if (btrfs_comp_keys_type(&key, path_current_disk_key(&path)))
    {
        goto out;
    }

    seek_pointer = offset;

    do
    {
        TRACE("Current extent: (%llu %u %llu) \n",
              path_current_disk_key(&path)->objectid,
              path_current_disk_key(&path)->type,
              path_current_disk_key(&path)->offset);

        extent = (struct btrfs_file_extent_item *) path_current_data(&path);

        offset_in_extent = seek_pointer;
        /* check if we need clean extent offset when switching to the next extent */
        if ((seek_pointer) >= path_current_disk_key(&path)->offset)
            offset_in_extent -= path_current_disk_key(&path)->offset;

        if (extent->type == BTRFS_FILE_EXTENT_INLINE)
        {
            rd = btrfs_read_extent_inline(&path, extent, offset_in_extent, size, buf);
        }
        else
        {
            rd = btrfs_read_extent_reg(&path, extent, offset_in_extent, size, buf);
        }

        if (rd == READ_ERROR)
        {
            ERR("Error while reading extent\n");
            seek_pointer = READ_ERROR;
            goto out;
        }

        buf += rd;
        seek_pointer += rd;
        size -= rd;
        TRACE("file_read size=%llu rd=%llu seek_pointer=%llu\n", size, rd, seek_pointer);

        if (!size)
            break;
    } while (!(res = next_slot(&key, &path)));

    if (res)
    {
        seek_pointer = READ_ERROR;
        goto out;
    }

    seek_pointer -= offset;
out:
    free_path(&path);
    return seek_pointer;
}
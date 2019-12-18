#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* item; } ;
typedef  TYPE_4__ traverse_ptr ;
struct TYPE_19__ {int /*<<< orphan*/  num_devices; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  csum_root_level; int /*<<< orphan*/  csum_root_generation; int /*<<< orphan*/  csum_root_addr; int /*<<< orphan*/  dev_root_level; int /*<<< orphan*/  dev_root_generation; int /*<<< orphan*/  dev_root_addr; int /*<<< orphan*/  fs_root_level; int /*<<< orphan*/  fs_tree_generation; int /*<<< orphan*/  fs_tree_addr; int /*<<< orphan*/  extent_root_level; int /*<<< orphan*/  extent_tree_generation; int /*<<< orphan*/  extent_tree_addr; int /*<<< orphan*/  chunk_root_level; int /*<<< orphan*/  chunk_tree_generation; int /*<<< orphan*/  chunk_tree_addr; int /*<<< orphan*/  root_level; int /*<<< orphan*/  root_tree_generation; int /*<<< orphan*/  root_tree_addr; } ;
typedef  TYPE_5__ superblock_backup ;
struct TYPE_17__ {int /*<<< orphan*/  num_devices; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  chunk_root_level; int /*<<< orphan*/  chunk_root_generation; int /*<<< orphan*/  chunk_tree_addr; int /*<<< orphan*/  root_level; int /*<<< orphan*/  generation; int /*<<< orphan*/  root_tree_addr; } ;
struct TYPE_20__ {TYPE_3__ superblock; int /*<<< orphan*/  root_root; } ;
typedef  TYPE_6__ device_extension ;
struct TYPE_22__ {scalar_t__ obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_21__ {int /*<<< orphan*/  root_level; int /*<<< orphan*/  generation; int /*<<< orphan*/  block_number; } ;
struct TYPE_15__ {scalar_t__ obj_id; scalar_t__ obj_type; } ;
struct TYPE_16__ {int size; scalar_t__ data; TYPE_1__ key; } ;
typedef  TYPE_7__ ROOT_ITEM ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_8__ KEY ;

/* Variables and functions */
 scalar_t__ BTRFS_ROOT_CHECKSUM ; 
 scalar_t__ BTRFS_ROOT_DEVTREE ; 
 scalar_t__ BTRFS_ROOT_EXTENT ; 
 scalar_t__ BTRFS_ROOT_FSTREE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_5__*,int) ; 
 scalar_t__ TYPE_ROOT_ITEM ; 
 int /*<<< orphan*/  find_item (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_backup_superblock(device_extension* Vcb, superblock_backup* sb, PIRP Irp) {
    KEY searchkey;
    traverse_ptr tp;

    RtlZeroMemory(sb, sizeof(superblock_backup));

    sb->root_tree_addr = Vcb->superblock.root_tree_addr;
    sb->root_tree_generation = Vcb->superblock.generation;
    sb->root_level = Vcb->superblock.root_level;

    sb->chunk_tree_addr = Vcb->superblock.chunk_tree_addr;
    sb->chunk_tree_generation = Vcb->superblock.chunk_root_generation;
    sb->chunk_root_level = Vcb->superblock.chunk_root_level;

    searchkey.obj_id = BTRFS_ROOT_EXTENT;
    searchkey.obj_type = TYPE_ROOT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    if (NT_SUCCESS(find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp))) {
        if (tp.item->key.obj_id == searchkey.obj_id && tp.item->key.obj_type == searchkey.obj_type && tp.item->size >= sizeof(ROOT_ITEM)) {
            ROOT_ITEM* ri = (ROOT_ITEM*)tp.item->data;

            sb->extent_tree_addr = ri->block_number;
            sb->extent_tree_generation = ri->generation;
            sb->extent_root_level = ri->root_level;
        }
    }

    searchkey.obj_id = BTRFS_ROOT_FSTREE;

    if (NT_SUCCESS(find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp))) {
        if (tp.item->key.obj_id == searchkey.obj_id && tp.item->key.obj_type == searchkey.obj_type && tp.item->size >= sizeof(ROOT_ITEM)) {
            ROOT_ITEM* ri = (ROOT_ITEM*)tp.item->data;

            sb->fs_tree_addr = ri->block_number;
            sb->fs_tree_generation = ri->generation;
            sb->fs_root_level = ri->root_level;
        }
    }

    searchkey.obj_id = BTRFS_ROOT_DEVTREE;

    if (NT_SUCCESS(find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp))) {
        if (tp.item->key.obj_id == searchkey.obj_id && tp.item->key.obj_type == searchkey.obj_type && tp.item->size >= sizeof(ROOT_ITEM)) {
            ROOT_ITEM* ri = (ROOT_ITEM*)tp.item->data;

            sb->dev_root_addr = ri->block_number;
            sb->dev_root_generation = ri->generation;
            sb->dev_root_level = ri->root_level;
        }
    }

    searchkey.obj_id = BTRFS_ROOT_CHECKSUM;

    if (NT_SUCCESS(find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp))) {
        if (tp.item->key.obj_id == searchkey.obj_id && tp.item->key.obj_type == searchkey.obj_type && tp.item->size >= sizeof(ROOT_ITEM)) {
            ROOT_ITEM* ri = (ROOT_ITEM*)tp.item->data;

            sb->csum_root_addr = ri->block_number;
            sb->csum_root_generation = ri->generation;
            sb->csum_root_level = ri->root_level;
        }
    }

    sb->total_bytes = Vcb->superblock.total_bytes;
    sb->bytes_used = Vcb->superblock.bytes_used;
    sb->num_devices = Vcb->superblock.num_devices;
}
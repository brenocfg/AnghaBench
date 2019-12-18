#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct btrfs_super_block {int dummy; } ;
struct btrfs_root_item {int /*<<< orphan*/  level; int /*<<< orphan*/  bytenr; } ;
struct btrfs_path {int dummy; } ;
struct BTRFS_INFO {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {scalar_t__ magic; int /*<<< orphan*/  root_level; int /*<<< orphan*/  root; } ;
struct TYPE_7__ {struct btrfs_root_item FsRoot; TYPE_1__ SuperBlock; int /*<<< orphan*/  DeviceId; } ;
typedef  int /*<<< orphan*/  DEVVTBL ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_TREE_OBJECTID ; 
 scalar_t__ BTRFS_MAGIC_N ; 
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_SUPER_INFO_OFFSET ; 
 int /*<<< orphan*/  const BtrFsFuncTable ; 
 TYPE_2__* BtrFsInfo ; 
 int /*<<< orphan*/  BtrFsSearchTreeType (struct btrfs_root_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_path*) ; 
 TYPE_2__* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TAG_BTRFS_INFO ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_crc32c () ; 
 int /*<<< orphan*/  btrfs_read_chunk_tree () ; 
 int /*<<< orphan*/  btrfs_read_sys_chunk_array () ; 
 int /*<<< orphan*/  disk_read (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  init_path (struct btrfs_path*) ; 
 scalar_t__ path_current_data (struct btrfs_path*) ; 

const DEVVTBL *BtrFsMount(ULONG DeviceId)
{
    struct btrfs_path path;
    struct btrfs_root_item fs_root_item;

    TRACE("Enter BtrFsMount(%lu)\n", DeviceId);

    BtrFsInfo = FrLdrTempAlloc(sizeof(struct BTRFS_INFO), TAG_BTRFS_INFO);
    if (!BtrFsInfo)
        return NULL;
    RtlZeroMemory(BtrFsInfo, sizeof(struct BTRFS_INFO));

    /* Read the SuperBlock */
    if (!disk_read(BTRFS_SUPER_INFO_OFFSET, &BtrFsInfo->SuperBlock, sizeof(struct btrfs_super_block)))
    {
        FrLdrTempFree(BtrFsInfo, TAG_BTRFS_INFO);
        return NULL;
    }

    /* Check if SuperBlock is valid. If yes, return BTRFS function table */
    if (BtrFsInfo->SuperBlock.magic != BTRFS_MAGIC_N)
    {
        FrLdrTempFree(BtrFsInfo, TAG_BTRFS_INFO);
        return NULL;
    }

    BtrFsInfo->DeviceId = DeviceId;
    TRACE("BtrFsMount(%lu) superblock magic ok\n", DeviceId);

    btrfs_init_crc32c();

    btrfs_read_sys_chunk_array();
    btrfs_read_chunk_tree();

    /* setup roots */
    fs_root_item.bytenr = BtrFsInfo->SuperBlock.root;
    fs_root_item.level = BtrFsInfo->SuperBlock.root_level;

    init_path(&path);
    if (!BtrFsSearchTreeType(&fs_root_item, BTRFS_FS_TREE_OBJECTID, BTRFS_ROOT_ITEM_KEY, &path))
    {
        FrLdrTempFree(BtrFsInfo, TAG_BTRFS_INFO);
        free_path(&path);
        return NULL;
    }

    BtrFsInfo->FsRoot = *(struct btrfs_root_item *) path_current_data(&path);

    free_path(&path);

    TRACE("BtrFsMount(%lu) success\n", DeviceId);
    return &BtrFsFuncTable;
}
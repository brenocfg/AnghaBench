#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_24__ {int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  otime; } ;
struct TYPE_29__ {int /*<<< orphan*/  Length; } ;
struct TYPE_21__ {scalar_t__ atts; scalar_t__ type; TYPE_13__ inode_item; scalar_t__ ads; TYPE_4__ adsdata; TYPE_3__* Vcb; TYPE_2__* subvol; scalar_t__ inode; } ;
typedef  TYPE_10__ fcb ;
struct TYPE_22__ {int /*<<< orphan*/  access; TYPE_9__* fileref; } ;
typedef  TYPE_11__ ccb ;
struct TYPE_34__ {TYPE_8__* parent; } ;
struct TYPE_33__ {TYPE_7__* fcb; } ;
struct TYPE_32__ {scalar_t__ atts; TYPE_13__ inode_item; } ;
struct TYPE_31__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_30__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_28__ {TYPE_10__* dummy_fcb; } ;
struct TYPE_27__ {scalar_t__ id; } ;
struct TYPE_26__ {void* HighPart; void* LowPart; } ;
struct TYPE_23__ {void* QuadPart; } ;
struct TYPE_25__ {int FileAttributes; int /*<<< orphan*/  EffectiveAccess; int /*<<< orphan*/  NumberOfLinks; scalar_t__ ReparseTag; TYPE_6__ EndOfFile; TYPE_5__ AllocationSize; TYPE_12__ ChangeTime; TYPE_12__ LastWriteTime; TYPE_12__ LastAccessTime; TYPE_12__ CreationTime; TYPE_1__ FileId; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_12__ LARGE_INTEGER ;
typedef  TYPE_13__ INODE_ITEM ;
typedef  TYPE_14__ FILE_STAT_INFORMATION ;

/* Variables and functions */
 scalar_t__ BTRFS_TYPE_BLOCKDEV ; 
 scalar_t__ BTRFS_TYPE_CHARDEV ; 
 scalar_t__ BTRFS_TYPE_FIFO ; 
 scalar_t__ BTRFS_TYPE_SOCKET ; 
 void* FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 scalar_t__ IO_REPARSE_TAG_LXSS_BLOCKDEV ; 
 scalar_t__ IO_REPARSE_TAG_LXSS_CHARDEV ; 
 scalar_t__ IO_REPARSE_TAG_LXSS_FIFO ; 
 scalar_t__ IO_REPARSE_TAG_LXSS_SOCKET ; 
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_12__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcb_alloc_size (TYPE_10__*) ; 
 scalar_t__ get_reparse_tag_fcb (TYPE_10__*) ; 
 void* unix_time_to_win (int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS fill_in_file_stat_information(FILE_STAT_INFORMATION* fsi, fcb* fcb, ccb* ccb, LONG* length) {
    INODE_ITEM* ii;

    fsi->FileId.LowPart = (uint32_t)fcb->inode;
    fsi->FileId.HighPart = (uint32_t)fcb->subvol->id;

    if (fcb->ads)
        ii = &ccb->fileref->parent->fcb->inode_item;
    else
        ii = &fcb->inode_item;

    if (fcb == fcb->Vcb->dummy_fcb) {
        LARGE_INTEGER time;

        KeQuerySystemTime(&time);
        fsi->CreationTime = fsi->LastAccessTime = fsi->LastWriteTime = fsi->ChangeTime = time;
    } else {
        fsi->CreationTime.QuadPart = unix_time_to_win(&ii->otime);
        fsi->LastAccessTime.QuadPart = unix_time_to_win(&ii->st_atime);
        fsi->LastWriteTime.QuadPart = unix_time_to_win(&ii->st_mtime);
        fsi->ChangeTime.QuadPart = unix_time_to_win(&ii->st_ctime);
    }

    if (fcb->ads) {
        fsi->AllocationSize.QuadPart = fsi->EndOfFile.QuadPart = fcb->adsdata.Length;
        fsi->FileAttributes = ccb->fileref->parent->fcb->atts == 0 ? FILE_ATTRIBUTE_NORMAL : ccb->fileref->parent->fcb->atts;
    } else {
        fsi->AllocationSize.QuadPart = fcb_alloc_size(fcb);
        fsi->EndOfFile.QuadPart = S_ISDIR(fcb->inode_item.st_mode) ? 0 : fcb->inode_item.st_size;
        fsi->FileAttributes = fcb->atts == 0 ? FILE_ATTRIBUTE_NORMAL : fcb->atts;
    }

    if (fcb->type == BTRFS_TYPE_SOCKET)
        fsi->ReparseTag = IO_REPARSE_TAG_LXSS_SOCKET;
    else if (fcb->type == BTRFS_TYPE_FIFO)
        fsi->ReparseTag = IO_REPARSE_TAG_LXSS_FIFO;
    else if (fcb->type == BTRFS_TYPE_CHARDEV)
        fsi->ReparseTag = IO_REPARSE_TAG_LXSS_CHARDEV;
    else if (fcb->type == BTRFS_TYPE_BLOCKDEV)
        fsi->ReparseTag = IO_REPARSE_TAG_LXSS_BLOCKDEV;
    else if (!(fsi->FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
        fsi->ReparseTag = 0;
    else
        fsi->ReparseTag = get_reparse_tag_fcb(fcb);

    if (fcb->type == BTRFS_TYPE_SOCKET || fcb->type == BTRFS_TYPE_FIFO || fcb->type == BTRFS_TYPE_CHARDEV || fcb->type == BTRFS_TYPE_BLOCKDEV)
        fsi->FileAttributes |= FILE_ATTRIBUTE_REPARSE_POINT;

    if (fcb->ads)
        fsi->NumberOfLinks = ccb->fileref->parent->fcb->inode_item.st_nlink;
    else
        fsi->NumberOfLinks = fcb->inode_item.st_nlink;

    fsi->EffectiveAccess = ccb->access;

    *length -= sizeof(FILE_STAT_INFORMATION);

    return STATUS_SUCCESS;
}
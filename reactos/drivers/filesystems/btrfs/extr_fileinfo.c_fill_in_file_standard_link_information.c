#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int delete_on_close; } ;
typedef  TYPE_2__ file_ref ;
struct TYPE_8__ {int /*<<< orphan*/  st_nlink; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  ads; TYPE_1__ inode_item; } ;
typedef  TYPE_3__ fcb ;
struct TYPE_11__ {int DeletePending; int Directory; int /*<<< orphan*/  TotalNumberOfLinks; int /*<<< orphan*/  NumberOfAccessibleLinks; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_4__ FILE_STANDARD_LINK_INFORMATION ;

/* Variables and functions */
 scalar_t__ BTRFS_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static NTSTATUS fill_in_file_standard_link_information(FILE_STANDARD_LINK_INFORMATION* fsli, fcb* fcb, file_ref* fileref, LONG* length) {
    TRACE("FileStandardLinkInformation\n");

    // FIXME - NumberOfAccessibleLinks should subtract open links which have been marked as delete_on_close

    fsli->NumberOfAccessibleLinks = fcb->inode_item.st_nlink;
    fsli->TotalNumberOfLinks = fcb->inode_item.st_nlink;
    fsli->DeletePending = fileref ? fileref->delete_on_close : false;
    fsli->Directory = (!fcb->ads && fcb->type == BTRFS_TYPE_DIRECTORY) ? true : false;

    *length -= sizeof(FILE_STANDARD_LINK_INFORMATION);

    return STATUS_SUCCESS;
}
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
struct TYPE_18__ {TYPE_3__* parent; } ;
typedef  TYPE_4__ file_ref ;
struct TYPE_19__ {scalar_t__ atts; scalar_t__ ads; TYPE_1__* Vcb; } ;
typedef  TYPE_5__ fcb ;
struct TYPE_20__ {void* QuadPart; } ;
struct TYPE_22__ {void* FileAttributes; TYPE_6__ ChangeTime; TYPE_6__ LastWriteTime; TYPE_6__ LastAccessTime; TYPE_6__ CreationTime; } ;
struct TYPE_21__ {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  otime; } ;
struct TYPE_17__ {TYPE_2__* fcb; } ;
struct TYPE_16__ {scalar_t__ atts; } ;
struct TYPE_15__ {TYPE_5__* dummy_fcb; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_6__ LARGE_INTEGER ;
typedef  TYPE_7__ INODE_ITEM ;
typedef  TYPE_8__ FILE_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 void* FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_6__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_8__*,int) ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 void* unix_time_to_win (int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS fill_in_file_basic_information(FILE_BASIC_INFORMATION* fbi, INODE_ITEM* ii, LONG* length, fcb* fcb, file_ref* fileref) {
    RtlZeroMemory(fbi, sizeof(FILE_BASIC_INFORMATION));

    *length -= sizeof(FILE_BASIC_INFORMATION);

    if (fcb == fcb->Vcb->dummy_fcb) {
        LARGE_INTEGER time;

        KeQuerySystemTime(&time);
        fbi->CreationTime = fbi->LastAccessTime = fbi->LastWriteTime = fbi->ChangeTime = time;
    } else {
        fbi->CreationTime.QuadPart = unix_time_to_win(&ii->otime);
        fbi->LastAccessTime.QuadPart = unix_time_to_win(&ii->st_atime);
        fbi->LastWriteTime.QuadPart = unix_time_to_win(&ii->st_mtime);
        fbi->ChangeTime.QuadPart = unix_time_to_win(&ii->st_ctime);
    }

    if (fcb->ads) {
        if (!fileref || !fileref->parent) {
            ERR("no fileref for stream\n");
            return STATUS_INTERNAL_ERROR;
        } else
            fbi->FileAttributes = fileref->parent->fcb->atts == 0 ? FILE_ATTRIBUTE_NORMAL : fileref->parent->fcb->atts;
    } else
        fbi->FileAttributes = fcb->atts == 0 ? FILE_ATTRIBUTE_NORMAL : fcb->atts;

    return STATUS_SUCCESS;
}
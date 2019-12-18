#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {int DeviceId; int /*<<< orphan*/ * Specific; TYPE_1__* FuncTable; } ;
struct TYPE_3__ {scalar_t__ (* Close ) (size_t) ;} ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ ESUCCESS ; 
 TYPE_2__* FileData ; 
 size_t MAX_FDS ; 
 scalar_t__ stub1 (size_t) ; 

ARC_STATUS ArcClose(ULONG FileId)
{
    ARC_STATUS Status;

    if (FileId >= MAX_FDS || !FileData[FileId].FuncTable)
        return EBADF;

    Status = FileData[FileId].FuncTable->Close(FileId);

    if (Status == ESUCCESS)
    {
        FileData[FileId].FuncTable = NULL;
        FileData[FileId].Specific = NULL;
        FileData[FileId].DeviceId = -1;
    }
    return Status;
}
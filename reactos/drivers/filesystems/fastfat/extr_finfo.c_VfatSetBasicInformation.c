#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
struct TYPE_12__ {int QuadPart; } ;
struct TYPE_17__ {int FileAttributes; TYPE_11__ LastWriteTime; TYPE_11__ LastAccessTime; TYPE_11__ CreationTime; } ;
struct TYPE_14__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; int /*<<< orphan*/  AccessDate; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  CreationDate; } ;
struct TYPE_13__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; int /*<<< orphan*/  AccessTime; int /*<<< orphan*/  AccessDate; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  CreationDate; } ;
struct TYPE_15__ {TYPE_2__ Fat; TYPE_1__ FatX; } ;
struct TYPE_16__ {int* Attributes; TYPE_3__ entry; } ;
typedef  TYPE_4__* PVFATFCB ;
typedef  int /*<<< orphan*/ * PFILE_OBJECT ;
typedef  TYPE_5__* PFILE_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/ * PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BooleanFlagOn (int,int) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FILE_ACTION_MODIFIED ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int FILE_ATTRIBUTE_TEMPORARY ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_ATTRIBUTES ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_CREATION ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_LAST_ACCESS ; 
 int /*<<< orphan*/  FILE_NOTIFY_CHANGE_LAST_WRITE ; 
 int /*<<< orphan*/  FsdSystemTimeToDosDateTime (int /*<<< orphan*/ *,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  VfatUpdateEntry (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int _A_VOLID ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_4__*) ; 
 int /*<<< orphan*/  vfatReportChange (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vfatVolumeIsFatX (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
NTSTATUS
VfatSetBasicInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB FCB,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_BASIC_INFORMATION BasicInfo)
{
    ULONG NotifyFilter;

    DPRINT("VfatSetBasicInformation()\n");

    ASSERT(NULL != FileObject);
    ASSERT(NULL != FCB);
    ASSERT(NULL != DeviceExt);
    ASSERT(NULL != BasicInfo);
    /* Check volume label bit */
    ASSERT(0 == (*FCB->Attributes & _A_VOLID));

    NotifyFilter = 0;

    if (BasicInfo->FileAttributes != 0)
    {
        UCHAR Attributes;

        Attributes = (BasicInfo->FileAttributes & (FILE_ATTRIBUTE_ARCHIVE |
                                                   FILE_ATTRIBUTE_SYSTEM |
                                                   FILE_ATTRIBUTE_HIDDEN |
                                                   FILE_ATTRIBUTE_DIRECTORY |
                                                   FILE_ATTRIBUTE_READONLY));

        if (vfatFCBIsDirectory(FCB))
        {
            if (BooleanFlagOn(BasicInfo->FileAttributes, FILE_ATTRIBUTE_TEMPORARY))
            {
                DPRINT("Setting temporary attribute on a directory!\n");
                return STATUS_INVALID_PARAMETER;
            }

            Attributes |= FILE_ATTRIBUTE_DIRECTORY;
        }
        else
        {
            if (BooleanFlagOn(BasicInfo->FileAttributes, FILE_ATTRIBUTE_DIRECTORY))
            {
                DPRINT("Setting directory attribute on a file!\n");
                return STATUS_INVALID_PARAMETER;
            }
        }

        if (Attributes != *FCB->Attributes)
        {
            *FCB->Attributes = Attributes;
            DPRINT("Setting attributes 0x%02x\n", *FCB->Attributes);
            NotifyFilter |= FILE_NOTIFY_CHANGE_ATTRIBUTES;
        }
    }

    if (vfatVolumeIsFatX(DeviceExt))
    {
        if (BasicInfo->CreationTime.QuadPart != 0 && BasicInfo->CreationTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->CreationTime,
                                       &FCB->entry.FatX.CreationDate,
                                       &FCB->entry.FatX.CreationTime);
            NotifyFilter |= FILE_NOTIFY_CHANGE_CREATION;
        }

        if (BasicInfo->LastAccessTime.QuadPart != 0 && BasicInfo->LastAccessTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->LastAccessTime,
                                       &FCB->entry.FatX.AccessDate,
                                       &FCB->entry.FatX.AccessTime);
            NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_ACCESS;
        }

        if (BasicInfo->LastWriteTime.QuadPart != 0 && BasicInfo->LastWriteTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->LastWriteTime,
                                       &FCB->entry.FatX.UpdateDate,
                                       &FCB->entry.FatX.UpdateTime);
            NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_WRITE;
        }
    }
    else
    {
        if (BasicInfo->CreationTime.QuadPart != 0 && BasicInfo->CreationTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->CreationTime,
                                       &FCB->entry.Fat.CreationDate,
                                       &FCB->entry.Fat.CreationTime);
            NotifyFilter |= FILE_NOTIFY_CHANGE_CREATION;
        }

        if (BasicInfo->LastAccessTime.QuadPart != 0 && BasicInfo->LastAccessTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->LastAccessTime,
                                       &FCB->entry.Fat.AccessDate,
                                       NULL);
            NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_ACCESS;
        }

        if (BasicInfo->LastWriteTime.QuadPart != 0 && BasicInfo->LastWriteTime.QuadPart != -1)
        {
            FsdSystemTimeToDosDateTime(DeviceExt,
                                       &BasicInfo->LastWriteTime,
                                       &FCB->entry.Fat.UpdateDate,
                                       &FCB->entry.Fat.UpdateTime);
            NotifyFilter |= FILE_NOTIFY_CHANGE_LAST_WRITE;
        }
    }

    VfatUpdateEntry(DeviceExt, FCB);

    if (NotifyFilter != 0)
    {
        vfatReportChange(DeviceExt,
                         FCB,
                         NotifyFilter,
                         FILE_ACTION_MODIFIED);
    }

    return STATUS_SUCCESS;
}
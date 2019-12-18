#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_12__ {scalar_t__ Status; } ;
struct TYPE_11__ {int QuadPart; } ;
struct TYPE_10__ {int NumberOfHeads; int SectorsPerTrack; int BytesPerSector; } ;
struct TYPE_9__ {int EndCylinderNumber; int StartCylinderNumber; int EndHeadNumber; int StartHeadNumber; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PIRP ;
typedef  TYPE_1__* PFORMAT_PARAMETERS ;
typedef  TYPE_2__* PDRIVE_MEDIA_CONSTANTS ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_4__ IO_STATUS_BLOCK ;

/* Variables and functions */
 size_t Drive2080Media2080 ; 
 TYPE_2__* DriveMediaConstants ; 
 int /*<<< orphan*/ * ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRP_MJ_WRITE ; 
 int /*<<< orphan*/ * IoBuildSynchronousFsdRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPoolCacheAligned ; 
 int /*<<< orphan*/  NonPagedPoolNxCacheAligned ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_PENDING ; 

NTSTATUS
FlopticalFormatMedia(
    PDEVICE_OBJECT DeviceObject,
    PFORMAT_PARAMETERS Format
    )
/*++

Routine Description:

    This routine is used to do perform a format tracks for the 20.8 MB
    floppy.  Because the device does not support format tracks and the full
    format takes a long time a write of zeros is done instead.

Arguments:

    DeviceObject - Supplies the device object to be tested.

    Format - Supplies the format parameters.

Return Value:

    Returns a status for the operation.

--*/
{
    IO_STATUS_BLOCK ioStatus;
    PIRP irp;
    KEVENT event;
    LARGE_INTEGER offset;
    ULONG length;
    PVOID buffer;
    PDRIVE_MEDIA_CONSTANTS driveMediaConstants;
    NTSTATUS status;

    PAGED_CODE();

    driveMediaConstants = &DriveMediaConstants[Drive2080Media2080];

    //
    // Calculate the length of the buffer.
    //

    length = ((Format->EndCylinderNumber - Format->StartCylinderNumber) *
        driveMediaConstants->NumberOfHeads +
        Format->EndHeadNumber - Format->StartHeadNumber + 1) *
        driveMediaConstants->SectorsPerTrack *
        driveMediaConstants->BytesPerSector;

#ifndef __REACTOS__
    buffer = ExAllocatePool(NonPagedPoolNxCacheAligned, length);
#else
    buffer = ExAllocatePool(NonPagedPoolCacheAligned, length);
#endif

    if (buffer == NULL) {
        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    RtlZeroMemory(buffer, length);

    offset.QuadPart =
    (Format->StartCylinderNumber * driveMediaConstants->NumberOfHeads +
    Format->StartHeadNumber) * driveMediaConstants->SectorsPerTrack *
    driveMediaConstants->BytesPerSector;

    //
    // Set the event object to the unsignaled state.
    // It will be used to signal request completion.
    //

    KeInitializeEvent(&event, NotificationEvent, FALSE);

    //
    // Build the synchronous request with data transfer.
    //

    irp = IoBuildSynchronousFsdRequest(
       IRP_MJ_WRITE,
       DeviceObject,
       buffer,
       length,
       &offset,
       &event,
       &ioStatus);

    if (irp != NULL) {
        status = IoCallDriver(DeviceObject, irp);

        if (status == STATUS_PENDING) {

            //
            // Wait for the request to complete if necessary.
            //

            KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        }

        //
        // If the call  driver suceeded then set the status to the status block.
        //

        if (NT_SUCCESS(status)) {
            status = ioStatus.Status;
        }
    } else {
       status = STATUS_INSUFFICIENT_RESOURCES;
    }

    ExFreePool(buffer);

    return(status);

}
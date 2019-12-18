#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_27__ {TYPE_6__* DeviceExtension; } ;
struct TYPE_26__ {int /*<<< orphan*/  IsDMF; } ;
struct TYPE_21__ {int LowPart; } ;
struct TYPE_25__ {int BytesPerSector; int TracksPerCylinder; int SectorsPerTrack; void* MediaType; TYPE_2__ Cylinders; } ;
struct TYPE_20__ {scalar_t__ LowPart; } ;
struct TYPE_22__ {int /*<<< orphan*/  DriverData; TYPE_1__ PartitionLength; } ;
struct TYPE_24__ {int /*<<< orphan*/  TimeOutValue; TYPE_3__ CommonExtension; TYPE_7__ DiskGeometry; } ;
struct TYPE_23__ {int CdbLength; int /*<<< orphan*/  TimeOutValue; scalar_t__* Cdb; } ;
struct TYPE_19__ {int NumberOfHeads; int MaximumTrack; int SectorsPerTrack; int BytesPerSector; void* MediaType; } ;
typedef  TYPE_4__* PVOID ;
typedef  TYPE_4__* PSCSI_REQUEST_BLOCK ;
typedef  TYPE_6__* PFUNCTIONAL_DEVICE_EXTENSION ;
typedef  TYPE_7__* PDISK_GEOMETRY ;
typedef  TYPE_8__* PDISK_DATA ;
typedef  TYPE_9__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ClassReadDriveCapacity (TYPE_9__*) ; 
 int /*<<< orphan*/  ClassSendSrbSynchronous (TYPE_9__*,TYPE_4__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_13__* DriveMediaConstants ; 
 TYPE_4__* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_4__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 size_t NUMBER_OF_DRIVE_MEDIA_COMBINATIONS ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  NonPagedPoolNx ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int RtlCompareMemory (char*,char*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 
 scalar_t__ SCSIOP_READ ; 
 int SCSI_REQUEST_BLOCK_SIZE ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 void* Unknown ; 

NTSTATUS
DetermineMediaType(
    PDEVICE_OBJECT DeviceObject
    )
/*++

Routine Description:

    This routine determines the floppy media type based on the size of the
    device.  The geometry information is set for the device object.

Arguments:

    DeviceObject - Supplies the device object to be tested.

Return Value:

    None

--*/
{
    PFUNCTIONAL_DEVICE_EXTENSION fdoExtension = DeviceObject->DeviceExtension;
    PDISK_GEOMETRY geometry;
    LONG index;
    NTSTATUS status;

    PAGED_CODE();

    geometry = &(fdoExtension->DiskGeometry);

    //
    // Issue ReadCapacity to update device extension
    // with information for current media.
    //

    status = ClassReadDriveCapacity(DeviceObject);

    if (!NT_SUCCESS(status)) {

       //
       // Set the media type to unknow and zero the geometry information.
       //

       geometry->MediaType = Unknown;

       return status;

    }

    //
    // Look at the capcity of disk to determine its type.
    //

    for (index = NUMBER_OF_DRIVE_MEDIA_COMBINATIONS - 1; index >= 0; index--) {

        //
        // Walk the table backward untill the drive capacity holds all of the
        // data and the bytes per setor are equal
        //

         if ((ULONG) (DriveMediaConstants[index].NumberOfHeads *
             (DriveMediaConstants[index].MaximumTrack + 1) *
             DriveMediaConstants[index].SectorsPerTrack *
             DriveMediaConstants[index].BytesPerSector) <=
             fdoExtension->CommonExtension.PartitionLength.LowPart &&
             DriveMediaConstants[index].BytesPerSector ==
             geometry->BytesPerSector) {

             geometry->MediaType = DriveMediaConstants[index].MediaType;
             geometry->TracksPerCylinder = DriveMediaConstants[index].NumberOfHeads;
             geometry->SectorsPerTrack = DriveMediaConstants[index].SectorsPerTrack;
             geometry->Cylinders.LowPart = DriveMediaConstants[index].MaximumTrack+1;
             break;
         }
    }

    if (index == -1) {

        //
        // Set the media type to unknow and zero the geometry information.
        //

        geometry->MediaType = Unknown;


    } else {
        //
        // DMF check breaks the insight SCSI floppy, so its disabled for that case
        //
        PDISK_DATA diskData = (PDISK_DATA) fdoExtension->CommonExtension.DriverData;

        // if (diskData->EnableDMF == TRUE) {

            //
            //check to see if DMF
            //

            PSCSI_REQUEST_BLOCK srb;
            PVOID               readData;

            //
            // Allocate a Srb for the read command.
            //

#ifndef __REACTOS__
            readData = ExAllocatePool(NonPagedPoolNx, geometry->BytesPerSector);
#else
            readData = ExAllocatePool(NonPagedPool, geometry->BytesPerSector);
#endif
            if (readData == NULL) {
                return STATUS_NO_MEMORY;
            }

#ifndef __REACTOS__
            srb = ExAllocatePool(NonPagedPoolNx, SCSI_REQUEST_BLOCK_SIZE);
#else
            srb = ExAllocatePool(NonPagedPool, SCSI_REQUEST_BLOCK_SIZE);
#endif

            if (srb == NULL) {

                ExFreePool(readData);
                return STATUS_NO_MEMORY;
            }

            RtlZeroMemory(readData, geometry->BytesPerSector);
            RtlZeroMemory(srb, SCSI_REQUEST_BLOCK_SIZE);

            srb->CdbLength = 10;
            srb->Cdb[0] = SCSIOP_READ;
            srb->Cdb[5] = 0;
            srb->Cdb[8] = (UCHAR) 1;

            //
            // Set timeout value.
            //

            srb->TimeOutValue = fdoExtension->TimeOutValue;

            //
            // Send the mode select data.
            //

            status = ClassSendSrbSynchronous(DeviceObject,
                      srb,
                      readData,
                      geometry->BytesPerSector,
                      FALSE
                      );

            if (NT_SUCCESS(status)) {
                char *pchar = (char *)readData;

                pchar += 3; //skip 3 bytes jump code

                // If the MSDMF3. signature is there then mark it as DMF diskette
                if (RtlCompareMemory(pchar, "MSDMF3.", 7) == 7) {
                    diskData->IsDMF = TRUE;
                }

            }
            ExFreePool(readData);
            ExFreePool(srb);
        // }// else
    }
    return status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_17__ {scalar_t__ NumberOfHeads; int MaximumTrack; scalar_t__ SectorsPerTrack; } ;
struct TYPE_16__ {size_t HighestDriveMediaType; } ;
struct TYPE_15__ {TYPE_3__* DeviceExtension; } ;
struct TYPE_14__ {scalar_t__ DriveType; } ;
struct TYPE_11__ {int /*<<< orphan*/  DriverData; } ;
struct TYPE_13__ {TYPE_1__ CommonExtension; } ;
struct TYPE_12__ {scalar_t__ PageLength; scalar_t__ NumberOfHeads; int* NumberOfCylinders; scalar_t__ SectorsPerTrack; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PMODE_FLEXIBLE_DISK_PAGE ;
typedef  TYPE_3__* PFUNCTIONAL_DEVICE_EXTENSION ;
typedef  TYPE_4__* PDISK_DATA ;
typedef  TYPE_5__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  MODE_PARAMETER_HEADER ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_2__* ClassFindModePage (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ClassModeSense (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DRIVE_TYPE_NONE ; 
 TYPE_7__* DriveMediaConstants ; 
 TYPE_6__* DriveMediaLimits ; 
 int /*<<< orphan*/ * ExAllocatePool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MODE_DATA_SIZE ; 
 int /*<<< orphan*/  MODE_FLEXIBLE_DISK_PAGE ; 
 int /*<<< orphan*/  MODE_PAGE_FLEXIBILE ; 
 size_t NUMBER_OF_DRIVE_MEDIA_COMBINATIONS ; 
 scalar_t__ NUMBER_OF_DRIVE_TYPES ; 
 int /*<<< orphan*/  NonPagedPoolCacheAligned ; 
 int /*<<< orphan*/  NonPagedPoolNxCacheAligned ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartWritePrecom ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ULONG
DetermineDriveType(
    PDEVICE_OBJECT DeviceObject
    )
/*++

Routine Description:

    The routine determines the device type so that the supported medias can be
    determined.  It does a mode sense for the default parameters.  This code
    assumes that the returned values are for the maximum device size.

Arguments:

    DeviceObject - Supplies the device object to be tested.

Return Value:

    None

--*/
{
    PFUNCTIONAL_DEVICE_EXTENSION fdoExtension = DeviceObject->DeviceExtension;
    PVOID modeData;
    PDISK_DATA diskData = (PDISK_DATA) fdoExtension->CommonExtension.DriverData;
    PMODE_FLEXIBLE_DISK_PAGE pageData;
    ULONG length;
    LONG index;
    UCHAR numberOfHeads;
    UCHAR sectorsPerTrack;
    USHORT maximumTrack;
    BOOLEAN applyFix = FALSE;

    PAGED_CODE();

    if (diskData->DriveType != DRIVE_TYPE_NONE) {
        return(diskData->DriveType);
    }

#ifndef __REACTOS__
    modeData = ExAllocatePool(NonPagedPoolNxCacheAligned, MODE_DATA_SIZE);
#else
    modeData = ExAllocatePool(NonPagedPoolCacheAligned, MODE_DATA_SIZE);
#endif

    if (modeData == NULL) {
        return(DRIVE_TYPE_NONE);
    }

    RtlZeroMemory(modeData, MODE_DATA_SIZE);

    length = ClassModeSense(DeviceObject,
                            modeData,
                            MODE_DATA_SIZE,
                            MODE_PAGE_FLEXIBILE);

    if (length < sizeof(MODE_PARAMETER_HEADER)) {

        //
        // Retry the request one more time
        // in case of a check condition.
        //
        length = ClassModeSense(DeviceObject,
                                modeData,
                                MODE_DATA_SIZE,
                                MODE_PAGE_FLEXIBILE);

        if (length < sizeof(MODE_PARAMETER_HEADER)) {

            ExFreePool(modeData);
            return(DRIVE_TYPE_NONE);
        }
    }

    //
    // Look for the flexible disk mode page.
    //

    pageData = ClassFindModePage( modeData,
                                  length,
                                  MODE_PAGE_FLEXIBILE,
                                  TRUE);

    //
    // Make sure the page is returned and is large enough.
    //

    if ((pageData != NULL) &&
        (pageData->PageLength + 2 >=
         (UCHAR)offsetof(MODE_FLEXIBLE_DISK_PAGE, StartWritePrecom))) {

       //
       // Pull out the heads, cylinders, and sectors.
       //

       numberOfHeads = pageData->NumberOfHeads;
       maximumTrack = pageData->NumberOfCylinders[1];
       maximumTrack |= pageData->NumberOfCylinders[0] << 8;
       sectorsPerTrack = pageData->SectorsPerTrack;


       //
       // Convert from number of cylinders to maximum track.
       //

       maximumTrack--;

       //
       // Search for the maximum supported media. Based on the number of heads,
       // sectors per track and number of cylinders
       //
       for (index = 0; index < NUMBER_OF_DRIVE_MEDIA_COMBINATIONS; index++) {

            //
            // Walk the table forward until the drive capacity holds all of the
            // data and the bytes per setor are equal
            //

            if (DriveMediaConstants[index].NumberOfHeads == numberOfHeads &&
                DriveMediaConstants[index].MaximumTrack == maximumTrack &&
                DriveMediaConstants[index].SectorsPerTrack ==sectorsPerTrack) {

                ExFreePool(modeData);

                //
                // index is now a drive media combination.  Compare this to
                // the maximum drive media type in the drive media table.
                //

                for (length = 0; length < NUMBER_OF_DRIVE_TYPES; length++) {

                    if (DriveMediaLimits[length].HighestDriveMediaType == index) {
                        return(length);
                    }
                }
                return(DRIVE_TYPE_NONE);
           }
       }

       // If the maximum track is greater than 8 bits then divide the
       // number of tracks by 3 and multiply the number of heads by 3.
       // This is a special case for the 20.8 MB floppy.
       //

       if (!applyFix && maximumTrack >= 0x0100) {
           maximumTrack++;
           maximumTrack /= 3;
           maximumTrack--;
           numberOfHeads *= 3;
       } else {
           ExFreePool(modeData);
           return(DRIVE_TYPE_NONE);
       }

    }

    ExFreePool(modeData);
    return(DRIVE_TYPE_NONE);
}
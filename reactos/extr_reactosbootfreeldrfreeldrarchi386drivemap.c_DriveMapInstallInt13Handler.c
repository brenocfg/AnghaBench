#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ USHORT ;
typedef  int ULONG ;
typedef  int PUCHAR ;
typedef  int /*<<< orphan*/ * PDRIVE_MAP_LIST ;
typedef  int /*<<< orphan*/  DRIVE_MAP_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateCacheData () ; 
 int DriveMapHandlerAddress ; 
 int DriveMapHandlerSegOff ; 
 scalar_t__ DriveMapInstalled ; 
 int /*<<< orphan*/  DriveMapInt13HandlerEnd ; 
 int /*<<< orphan*/  DriveMapInt13HandlerMapList ; 
 int /*<<< orphan*/  DriveMapInt13HandlerStart ; 
 int DriveMapOldInt13HandlerAddress ; 
 int OldInt13HandlerAddress ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ ULongToPtr (int) ; 
 int /*<<< orphan*/ * UlongToPtr (int) ; 

VOID DriveMapInstallInt13Handler(PDRIVE_MAP_LIST DriveMap)
{
    ULONG*  RealModeIVT = (ULONG*)UlongToPtr(0x00000000);
    USHORT* BiosLowMemorySize = (USHORT*)ULongToPtr(0x00000413);

    if (!DriveMapInstalled)
    {
        // Get the old INT 13h handler address from the vector table
        OldInt13HandlerAddress = RealModeIVT[0x13];

        // Decrease the size of low memory
        (*BiosLowMemorySize)--;

        // Get linear address for drive map handler
        DriveMapHandlerAddress = (ULONG)(*BiosLowMemorySize) << 10;

        // Convert to segment:offset style address
        DriveMapHandlerSegOff = (DriveMapHandlerAddress << 12) & 0xffff0000;
    }

    // Copy the drive map structure to the proper place
    RtlCopyMemory(&DriveMapInt13HandlerMapList, DriveMap, sizeof(DRIVE_MAP_LIST));

    // Set the address of the BIOS INT 13h handler
    DriveMapOldInt13HandlerAddress = OldInt13HandlerAddress;

    // Copy the code to our reserved area
    RtlCopyMemory(UlongToPtr(DriveMapHandlerAddress),
                  &DriveMapInt13HandlerStart,
                  ((PUCHAR)&DriveMapInt13HandlerEnd - (PUCHAR)&DriveMapInt13HandlerStart));

    // Update the IVT
    RealModeIVT[0x13] = DriveMapHandlerSegOff;

    CacheInvalidateCacheData();
    DriveMapInstalled = TRUE;
}
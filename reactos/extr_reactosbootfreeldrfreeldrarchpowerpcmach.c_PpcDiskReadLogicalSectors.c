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
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BootPart ; 
 int FALSE ; 
 int ofw_open (int /*<<< orphan*/ ) ; 
 int ofw_read (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_seek (int,int,int) ; 
 int part_handle ; 
 int /*<<< orphan*/  printf (char*,...) ; 

BOOLEAN PpcDiskReadLogicalSectors( ULONG DriveNumber, ULONGLONG SectorNumber,
                   ULONG SectorCount, PVOID Buffer ) {
    int rlen = 0;

    if( part_handle == -1 ) {
    part_handle = ofw_open( BootPart );

    if( part_handle == -1 ) {
        printf("Could not open any disk devices we know about\n");
        return FALSE;
    }
    }

    if( part_handle == -1 ) {
    printf("Got partition handle %x\n", part_handle);
    return FALSE;
    }

    if( ofw_seek( part_handle,
           (ULONG)(SectorNumber >> 25),
           (ULONG)((SectorNumber * 512) & 0xffffffff) ) ) {
    printf("Seek to %x failed\n", (ULONG)(SectorNumber * 512));
    return FALSE;
    }

    rlen = ofw_read( part_handle, Buffer, (ULONG)(SectorCount * 512) );
    return rlen > 0;
}
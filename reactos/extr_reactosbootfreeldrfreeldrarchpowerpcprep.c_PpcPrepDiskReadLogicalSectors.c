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
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ide1_desc ; 
 int /*<<< orphan*/  ide_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ide_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

BOOLEAN PpcPrepDiskReadLogicalSectors
( ULONG DriveNumber, ULONGLONG SectorNumber,
  ULONG SectorCount, PVOID Buffer ) {
    int secct;

    for(secct = 0; secct < SectorCount; secct++)
    {
    ide_seek(&ide1_desc, SectorNumber + secct, 0);
    ide_read(&ide1_desc, ((PCHAR)Buffer) + secct * 512, 512);
    }
    /* Never give up! */
    return TRUE;
}
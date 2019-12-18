#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {int BytesPerSector; int Heads; int Sectors; } ;
typedef  TYPE_1__* PGEOMETRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  printf (char*,int) ; 

BOOLEAN PpcDiskGetDriveGeometry( ULONG DriveNumber, PGEOMETRY DriveGeometry ) {
    printf("GetGeometry(%d)\n", DriveNumber);
    DriveGeometry->BytesPerSector = 512;
    DriveGeometry->Heads = 16;
    DriveGeometry->Sectors = 63;
    return TRUE;
}
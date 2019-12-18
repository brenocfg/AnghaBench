#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  HwIdle; int /*<<< orphan*/  HwDetect; int /*<<< orphan*/  GetMemoryMap; int /*<<< orphan*/  VideoGetDisplaySize; int /*<<< orphan*/  VideoSetDisplayMode; int /*<<< orphan*/  VideoClearScreen; int /*<<< orphan*/  ConsGetCh; int /*<<< orphan*/  ConsKbHit; int /*<<< orphan*/  DiskReadLogicalSectors; int /*<<< orphan*/  ConsPutChar; } ;

/* Variables and functions */
 int /*<<< orphan*/  BootMain (char*) ; 
 char* FrLdrVersionString ; 
 TYPE_1__ MachVtbl ; 
 int /*<<< orphan*/  PcPrepHwIdle ; 
 int /*<<< orphan*/  PpcPrepConsGetCh ; 
 int /*<<< orphan*/  PpcPrepConsKbHit ; 
 int /*<<< orphan*/  PpcPrepDiskReadLogicalSectors ; 
 int /*<<< orphan*/  PpcPrepGetMemoryMap ; 
 int /*<<< orphan*/  PpcPrepHwDetect ; 
 int /*<<< orphan*/  PpcPrepPutChar ; 
 int /*<<< orphan*/  PpcPrepVideoClearScreen ; 
 int /*<<< orphan*/  PpcPrepVideoGetDisplaySize ; 
 int /*<<< orphan*/  PpcPrepVideoSetDisplayMode ; 
 int /*<<< orphan*/  ide1_desc ; 
 int /*<<< orphan*/  ide_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void PpcPrepInit()
{
    MachVtbl.ConsPutChar = PpcPrepPutChar;

    printf("Serial on\n");

    ide_setup( &ide1_desc );

    MachVtbl.DiskReadLogicalSectors = PpcPrepDiskReadLogicalSectors;

    MachVtbl.ConsKbHit   = PpcPrepConsKbHit;
    MachVtbl.ConsGetCh   = PpcPrepConsGetCh;

    MachVtbl.VideoClearScreen = PpcPrepVideoClearScreen;
    MachVtbl.VideoSetDisplayMode = PpcPrepVideoSetDisplayMode;
    MachVtbl.VideoGetDisplaySize = PpcPrepVideoGetDisplaySize;

    MachVtbl.GetMemoryMap = PpcPrepGetMemoryMap;
    MachVtbl.HwDetect = PpcPrepHwDetect;
    MachVtbl.HwIdle = PcPrepHwIdle;

    printf( "FreeLDR version [%s]\n", FrLdrVersionString );

    BootMain( "" );
}
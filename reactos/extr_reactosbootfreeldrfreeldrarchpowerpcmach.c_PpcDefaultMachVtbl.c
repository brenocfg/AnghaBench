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
struct TYPE_2__ {int /*<<< orphan*/  HwIdle; int /*<<< orphan*/  HwDetect; int /*<<< orphan*/  GetTime; int /*<<< orphan*/  DiskGetCacheableBlockCount; int /*<<< orphan*/  DiskGetDriveGeometry; int /*<<< orphan*/  DiskReadLogicalSectors; int /*<<< orphan*/  DiskGetBootPath; int /*<<< orphan*/  GetMemoryMap; int /*<<< orphan*/  VideoSync; int /*<<< orphan*/  VideoGetPaletteColor; int /*<<< orphan*/  VideoSetPaletteColor; int /*<<< orphan*/  VideoIsPaletteFixed; int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM; int /*<<< orphan*/  VideoPutChar; int /*<<< orphan*/  VideoHideShowTextCursor; int /*<<< orphan*/  VideoSetTextCursorPosition; int /*<<< orphan*/  VideoGetBufferSize; int /*<<< orphan*/  VideoGetDisplaySize; int /*<<< orphan*/  VideoSetDisplayMode; int /*<<< orphan*/  VideoClearScreen; int /*<<< orphan*/  ConsGetCh; int /*<<< orphan*/  ConsKbHit; int /*<<< orphan*/  ConsPutChar; } ;

/* Variables and functions */
 TYPE_1__ MachVtbl ; 
 int /*<<< orphan*/  PpcConsGetCh ; 
 int /*<<< orphan*/  PpcConsKbHit ; 
 int /*<<< orphan*/  PpcDiskGetBootPath ; 
 int /*<<< orphan*/  PpcDiskGetCacheableBlockCount ; 
 int /*<<< orphan*/  PpcDiskGetDriveGeometry ; 
 int /*<<< orphan*/  PpcDiskReadLogicalSectors ; 
 int /*<<< orphan*/  PpcGetMemoryMap ; 
 int /*<<< orphan*/  PpcGetTime ; 
 int /*<<< orphan*/  PpcHwDetect ; 
 int /*<<< orphan*/  PpcHwIdle ; 
 int /*<<< orphan*/  PpcOfwPutChar ; 
 int /*<<< orphan*/  PpcVideoClearScreen ; 
 int /*<<< orphan*/  PpcVideoCopyOffScreenBufferToVRAM ; 
 int /*<<< orphan*/  PpcVideoGetBufferSize ; 
 int /*<<< orphan*/  PpcVideoGetDisplaySize ; 
 int /*<<< orphan*/  PpcVideoGetPaletteColor ; 
 int /*<<< orphan*/  PpcVideoHideShowTextCursor ; 
 int /*<<< orphan*/  PpcVideoIsPaletteFixed ; 
 int /*<<< orphan*/  PpcVideoPutChar ; 
 int /*<<< orphan*/  PpcVideoSetDisplayMode ; 
 int /*<<< orphan*/  PpcVideoSetPaletteColor ; 
 int /*<<< orphan*/  PpcVideoSetTextCursorPosition ; 
 int /*<<< orphan*/  PpcVideoSync ; 

void PpcDefaultMachVtbl()
{
    MachVtbl.ConsPutChar = PpcOfwPutChar;
    MachVtbl.ConsKbHit   = PpcConsKbHit;
    MachVtbl.ConsGetCh   = PpcConsGetCh;
    MachVtbl.VideoClearScreen = PpcVideoClearScreen;
    MachVtbl.VideoSetDisplayMode = PpcVideoSetDisplayMode;
    MachVtbl.VideoGetDisplaySize = PpcVideoGetDisplaySize;
    MachVtbl.VideoGetBufferSize = PpcVideoGetBufferSize;
    MachVtbl.VideoSetTextCursorPosition = PpcVideoSetTextCursorPosition;
    MachVtbl.VideoHideShowTextCursor = PpcVideoHideShowTextCursor;
    MachVtbl.VideoPutChar = PpcVideoPutChar;
    MachVtbl.VideoCopyOffScreenBufferToVRAM =
        PpcVideoCopyOffScreenBufferToVRAM;
    MachVtbl.VideoIsPaletteFixed = PpcVideoIsPaletteFixed;
    MachVtbl.VideoSetPaletteColor = PpcVideoSetPaletteColor;
    MachVtbl.VideoGetPaletteColor = PpcVideoGetPaletteColor;
    MachVtbl.VideoSync = PpcVideoSync;

    MachVtbl.GetMemoryMap = PpcGetMemoryMap;

    MachVtbl.DiskGetBootPath = PpcDiskGetBootPath;
    MachVtbl.DiskReadLogicalSectors = PpcDiskReadLogicalSectors;
    MachVtbl.DiskGetDriveGeometry = PpcDiskGetDriveGeometry;
    MachVtbl.DiskGetCacheableBlockCount = PpcDiskGetCacheableBlockCount;

    MachVtbl.GetTime = PpcGetTime;

    MachVtbl.HwDetect = PpcHwDetect;
    MachVtbl.HwIdle = PpcHwIdle;
}
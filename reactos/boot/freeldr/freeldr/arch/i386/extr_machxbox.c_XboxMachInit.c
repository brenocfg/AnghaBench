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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  HwIdle; int /*<<< orphan*/  HwDetect; int /*<<< orphan*/  InitializeBootDevices; int /*<<< orphan*/  GetTime; int /*<<< orphan*/  DiskGetCacheableBlockCount; int /*<<< orphan*/  DiskGetDriveGeometry; int /*<<< orphan*/  DiskReadLogicalSectors; int /*<<< orphan*/  GetFloppyCount; int /*<<< orphan*/  GetExtendedBIOSData; int /*<<< orphan*/  GetMemoryMap; int /*<<< orphan*/  PrepareForReactOS; int /*<<< orphan*/  Beep; int /*<<< orphan*/  VideoSync; int /*<<< orphan*/  VideoGetPaletteColor; int /*<<< orphan*/  VideoSetPaletteColor; int /*<<< orphan*/  VideoIsPaletteFixed; int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM; int /*<<< orphan*/  VideoPutChar; int /*<<< orphan*/  VideoHideShowTextCursor; int /*<<< orphan*/  VideoSetTextCursorPosition; int /*<<< orphan*/  VideoGetFontsFromFirmware; int /*<<< orphan*/  VideoGetBufferSize; int /*<<< orphan*/  VideoGetDisplaySize; int /*<<< orphan*/  VideoSetDisplayMode; int /*<<< orphan*/  VideoClearScreen; int /*<<< orphan*/  ConsGetCh; int /*<<< orphan*/  ConsKbHit; int /*<<< orphan*/  ConsPutChar; } ;

/* Variables and functions */
 TYPE_1__ MachVtbl ; 
 int /*<<< orphan*/  PcBeep ; 
 int /*<<< orphan*/  PcInitializeBootDevices ; 
 int /*<<< orphan*/  XboxConsGetCh ; 
 int /*<<< orphan*/  XboxConsKbHit ; 
 int /*<<< orphan*/  XboxConsPutChar ; 
 int /*<<< orphan*/  XboxDiskGetCacheableBlockCount ; 
 int /*<<< orphan*/  XboxDiskGetDriveGeometry ; 
 int /*<<< orphan*/  XboxDiskReadLogicalSectors ; 
 int /*<<< orphan*/  XboxGetExtendedBIOSData ; 
 int /*<<< orphan*/  XboxGetFloppyCount ; 
 int /*<<< orphan*/  XboxGetTime ; 
 int /*<<< orphan*/  XboxHwDetect ; 
 int /*<<< orphan*/  XboxHwIdle ; 
 int /*<<< orphan*/  XboxMemGetMemoryMap ; 
 int /*<<< orphan*/  XboxMemInit () ; 
 int /*<<< orphan*/  XboxPrepareForReactOS ; 
 int /*<<< orphan*/  XboxSetLED (char*) ; 
 int /*<<< orphan*/  XboxVideoClearScreen ; 
 int /*<<< orphan*/  XboxVideoCopyOffScreenBufferToVRAM ; 
 int /*<<< orphan*/  XboxVideoGetBufferSize ; 
 int /*<<< orphan*/  XboxVideoGetDisplaySize ; 
 int /*<<< orphan*/  XboxVideoGetFontsFromFirmware ; 
 int /*<<< orphan*/  XboxVideoGetPaletteColor ; 
 int /*<<< orphan*/  XboxVideoHideShowTextCursor ; 
 int /*<<< orphan*/  XboxVideoInit () ; 
 int /*<<< orphan*/  XboxVideoIsPaletteFixed ; 
 int /*<<< orphan*/  XboxVideoPutChar ; 
 int /*<<< orphan*/  XboxVideoSetDisplayMode ; 
 int /*<<< orphan*/  XboxVideoSetPaletteColor ; 
 int /*<<< orphan*/  XboxVideoSetTextCursorPosition ; 
 int /*<<< orphan*/  XboxVideoSync ; 

VOID
XboxMachInit(const char *CmdLine)
{
    /* Set LEDs to red before anything is initialized */
    XboxSetLED("rrrr");

    /* Initialize our stuff */
    XboxMemInit();
    XboxVideoInit();

    /* Setup vtbl */
    MachVtbl.ConsPutChar = XboxConsPutChar;
    MachVtbl.ConsKbHit = XboxConsKbHit;
    MachVtbl.ConsGetCh = XboxConsGetCh;
    MachVtbl.VideoClearScreen = XboxVideoClearScreen;
    MachVtbl.VideoSetDisplayMode = XboxVideoSetDisplayMode;
    MachVtbl.VideoGetDisplaySize = XboxVideoGetDisplaySize;
    MachVtbl.VideoGetBufferSize = XboxVideoGetBufferSize;
    MachVtbl.VideoGetFontsFromFirmware = XboxVideoGetFontsFromFirmware;
    MachVtbl.VideoSetTextCursorPosition = XboxVideoSetTextCursorPosition;
    MachVtbl.VideoHideShowTextCursor = XboxVideoHideShowTextCursor;
    MachVtbl.VideoPutChar = XboxVideoPutChar;
    MachVtbl.VideoCopyOffScreenBufferToVRAM = XboxVideoCopyOffScreenBufferToVRAM;
    MachVtbl.VideoIsPaletteFixed = XboxVideoIsPaletteFixed;
    MachVtbl.VideoSetPaletteColor = XboxVideoSetPaletteColor;
    MachVtbl.VideoGetPaletteColor = XboxVideoGetPaletteColor;
    MachVtbl.VideoSync = XboxVideoSync;
    MachVtbl.Beep = PcBeep;
    MachVtbl.PrepareForReactOS = XboxPrepareForReactOS;
    MachVtbl.GetMemoryMap = XboxMemGetMemoryMap;
    MachVtbl.GetExtendedBIOSData = XboxGetExtendedBIOSData;
    MachVtbl.GetFloppyCount = XboxGetFloppyCount;
    MachVtbl.DiskReadLogicalSectors = XboxDiskReadLogicalSectors;
    MachVtbl.DiskGetDriveGeometry = XboxDiskGetDriveGeometry;
    MachVtbl.DiskGetCacheableBlockCount = XboxDiskGetCacheableBlockCount;
    MachVtbl.GetTime = XboxGetTime;
    MachVtbl.InitializeBootDevices = PcInitializeBootDevices;
    MachVtbl.HwDetect = XboxHwDetect;
    MachVtbl.HwIdle = XboxHwIdle;

    /* Set LEDs to orange after init */
    XboxSetLED("oooo");
}
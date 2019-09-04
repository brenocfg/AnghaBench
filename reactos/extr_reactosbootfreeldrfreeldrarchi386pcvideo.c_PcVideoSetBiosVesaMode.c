#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_5__ {int ax; int /*<<< orphan*/  bx; } ;
struct TYPE_6__ {TYPE_1__ w; } ;
typedef  TYPE_2__ REGS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
PcVideoSetBiosVesaMode(USHORT Mode)
{
  REGS Regs;

  /* Int 10h AX=4F02h
   * VESA SuperVGA BIOS - SET SuperVGA VIDEO MODE
   *
   * AX = 4F02h
   * BX = new video mode
   * ES:DI -> (VBE 3.0+) CRTC information block, bit mode bit 11 set
   * Return:
   * AL = 4Fh if function supported
   * AH = status
   * 00h successful
   * 01h failed
   *
   * Values for VESA video mode:
   * 00h-FFh OEM video modes (see #00010 at AH=00h)
   * 100h   640x400x256
   * 101h   640x480x256
   * 102h   800x600x16
   * 103h   800x600x256
   * 104h   1024x768x16
   * 105h   1024x768x256
   * 106h   1280x1024x16
   * 107h   1280x1024x256
   * 108h   80x60 text
   * 109h   132x25 text
   * 10Ah   132x43 text
   * 10Bh   132x50 text
   * 10Ch   132x60 text
   * ---VBE v1.2+ ---
   * 10Dh   320x200x32K
   * 10Eh   320x200x64K
   * 10Fh   320x200x16M
   * 110h   640x480x32K
   * 111h   640x480x64K
   * 112h   640x480x16M
   * 113h   800x600x32K
   * 114h   800x600x64K
   * 115h   800x600x16M
   * 116h   1024x768x32K
   * 117h   1024x768x64K
   * 118h   1024x768x16M
   * 119h   1280x1024x32K (1:5:5:5)
   * 11Ah   1280x1024x64K (5:6:5)
   * 11Bh   1280x1024x16M
   * ---VBE 2.0+ ---
   * 120h   1600x1200x256
   * 121h   1600x1200x32K
   * 122h   1600x1200x64K
   * 81FFh   special full-memory access mode
   *
   * Notes: The special mode 81FFh preserves the contents of the video memory and gives
   * access to all of the memory; VESA recommends that the special mode be a packed-pixel
   * mode. For VBE 2.0+, it is required that the VBE implement the mode, but not place it
   * in the list of available modes (mode information for this mode can be queried
   * directly, however).. As of VBE 2.0, VESA will no longer define video mode numbers
   */
  Regs.w.ax = 0x4F02;
  Regs.w.bx = Mode;
  Int386(0x10, &Regs, &Regs);

  if (0x004F != Regs.w.ax)
    {
      return FALSE;
    }

  return TRUE;
}
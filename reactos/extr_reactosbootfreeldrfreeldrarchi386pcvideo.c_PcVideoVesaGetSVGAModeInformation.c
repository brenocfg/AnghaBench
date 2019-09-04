#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_10__ {int /*<<< orphan*/  ReservedMaskPosition; int /*<<< orphan*/  ReservedMaskSize; int /*<<< orphan*/  BlueMaskPosition; int /*<<< orphan*/  BlueMaskSize; int /*<<< orphan*/  GreenMaskPosition; int /*<<< orphan*/  GreenMaskSize; int /*<<< orphan*/  RedMaskPosition; int /*<<< orphan*/  RedMaskSize; int /*<<< orphan*/  NumberOfImagePanes; int /*<<< orphan*/  BankSize; int /*<<< orphan*/  MemoryModel; int /*<<< orphan*/  NumberOfBanks; int /*<<< orphan*/  BitsPerPixel; int /*<<< orphan*/  NumberOfMemoryPlanes; int /*<<< orphan*/  CharacterHeightInPixels; int /*<<< orphan*/  CharacterWidthInPixels; int /*<<< orphan*/  HeightInPixels; int /*<<< orphan*/  WidthInPixels; int /*<<< orphan*/  BytesPerScanLine; int /*<<< orphan*/  WindowPositioningFunction; int /*<<< orphan*/  WindowBStartSegment; int /*<<< orphan*/  WindowAStartSegment; int /*<<< orphan*/  WindowSize; int /*<<< orphan*/  WindowGranularity; int /*<<< orphan*/  WindowsAttributesB; int /*<<< orphan*/  WindowAttributesA; int /*<<< orphan*/  ModeAttributes; } ;
struct TYPE_8__ {int ax; int /*<<< orphan*/  di; int /*<<< orphan*/  es; int /*<<< orphan*/  cx; } ;
struct TYPE_9__ {TYPE_1__ w; } ;
typedef  int /*<<< orphan*/  SVGA_MODE_INFORMATION ;
typedef  TYPE_2__ REGS ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PSVGA_MODE_INFORMATION ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BIOSCALLBUFFER ; 
 int /*<<< orphan*/  BIOSCALLBUFOFFSET ; 
 int /*<<< orphan*/  BIOSCALLBUFSEGMENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
PcVideoVesaGetSVGAModeInformation(USHORT Mode, PSVGA_MODE_INFORMATION ModeInformation)
{
  REGS Regs;

  RtlZeroMemory((PVOID)BIOSCALLBUFFER, 256);

  /* VESA SuperVGA BIOS - GET SuperVGA MODE INFORMATION
   * AX = 4F01h
   * CX = SuperVGA video mode (see #04082 for bitfields)
   * ES:DI -> 256-byte buffer for mode information (see #00079)
   * Return:
   * AL = 4Fh if function supported
   * AH = status
   * 00h successful
   * ES:DI buffer filled
   * 01h failed
   *
   * Desc: Determine the attributes of the specified video mode
   *
   * Note: While VBE 1.1 and higher will zero out all unused bytes
   * of the buffer, v1.0 did not, so applications that want to be
   * backward compatible should clear the buffer before calling
   */
  Regs.w.ax = 0x4F01;
  Regs.w.cx = Mode;
  Regs.w.es = BIOSCALLBUFSEGMENT;
  Regs.w.di = BIOSCALLBUFOFFSET;
  Int386(0x10, &Regs, &Regs);

  if (Regs.w.ax != 0x004F)
    {
      return FALSE;
    }

  RtlCopyMemory(ModeInformation, (PVOID)BIOSCALLBUFFER, sizeof(SVGA_MODE_INFORMATION));

  TRACE("\n");
  TRACE("BiosVesaGetSVGAModeInformation() mode 0x%x\n", Mode);
  TRACE("ModeAttributes = 0x%x\n", ModeInformation->ModeAttributes);
  TRACE("WindowAttributesA = 0x%x\n", ModeInformation->WindowAttributesA);
  TRACE("WindowAttributesB = 0x%x\n", ModeInformation->WindowsAttributesB);
  TRACE("WindowGranularity = %dKB\n", ModeInformation->WindowGranularity);
  TRACE("WindowSize = %dKB\n", ModeInformation->WindowSize);
  TRACE("WindowAStartSegment = 0x%x\n", ModeInformation->WindowAStartSegment);
  TRACE("WindowBStartSegment = 0x%x\n", ModeInformation->WindowBStartSegment);
  TRACE("WindowPositioningFunction = 0x%x\n", ModeInformation->WindowPositioningFunction);
  TRACE("BytesPerScanLine = %d\n", ModeInformation->BytesPerScanLine);
  TRACE("WidthInPixels = %d\n", ModeInformation->WidthInPixels);
  TRACE("HeightInPixels = %d\n", ModeInformation->HeightInPixels);
  TRACE("CharacterWidthInPixels = %d\n", ModeInformation->CharacterWidthInPixels);
  TRACE("CharacterHeightInPixels = %d\n", ModeInformation->CharacterHeightInPixels);
  TRACE("NumberOfMemoryPlanes = %d\n", ModeInformation->NumberOfMemoryPlanes);
  TRACE("BitsPerPixel = %d\n", ModeInformation->BitsPerPixel);
  TRACE("NumberOfBanks = %d\n", ModeInformation->NumberOfBanks);
  TRACE("MemoryModel = %d\n", ModeInformation->MemoryModel);
  TRACE("BankSize = %d\n", ModeInformation->BankSize);
  TRACE("NumberOfImagePlanes = %d\n", ModeInformation->NumberOfImagePanes);
  TRACE("---VBE v1.2+ ---\n");
  TRACE("RedMaskSize = %d\n", ModeInformation->RedMaskSize);
  TRACE("RedMaskPosition = %d\n", ModeInformation->RedMaskPosition);
  TRACE("GreenMaskSize = %d\n", ModeInformation->GreenMaskSize);
  TRACE("GreenMaskPosition = %d\n", ModeInformation->GreenMaskPosition);
  TRACE("BlueMaskSize = %d\n", ModeInformation->BlueMaskSize);
  TRACE("BlueMaskPosition = %d\n", ModeInformation->BlueMaskPosition);
  TRACE("ReservedMaskSize = %d\n", ModeInformation->ReservedMaskSize);
  TRACE("ReservedMaskPosition = %d\n", ModeInformation->ReservedMaskPosition);
  TRACE("\n");

  return TRUE;
}
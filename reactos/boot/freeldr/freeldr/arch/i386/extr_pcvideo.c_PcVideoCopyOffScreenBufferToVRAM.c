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
typedef  int USHORT ;
typedef  int ULONG ;
struct TYPE_2__ {int WindowGranularity; int HeightInPixels; int BytesPerScanLine; } ;
typedef  char* PVOID ;

/* Variables and functions */
 scalar_t__ DisplayMode ; 
 int PcVideoGetBufferSize () ; 
 int /*<<< orphan*/  PcVideoSetMemoryBank (int) ; 
 int /*<<< orphan*/  RtlCopyMemory (char*,char*,int) ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 
 scalar_t__ VIDEOTEXT_MEM_ADDRESS ; 
 scalar_t__ VIDEOVGA_MEM_ADDRESS ; 
 scalar_t__ VesaVideoMode ; 
 TYPE_1__ VesaVideoModeInformation ; 
 scalar_t__ VideoGraphicsMode ; 
 scalar_t__ VideoTextMode ; 

VOID
PcVideoCopyOffScreenBufferToVRAM(PVOID Buffer)
{
  USHORT BanksToCopy;
  ULONG BytesInLastBank;
  USHORT CurrentBank;
  ULONG BankSize;

  /* PcVideoWaitForVerticalRetrace(); */

  /* Text mode (BIOS or VESA) */
  if (VideoTextMode == DisplayMode)
    {
      RtlCopyMemory((PVOID) VIDEOTEXT_MEM_ADDRESS, Buffer, PcVideoGetBufferSize());
    }
  /* VESA graphics mode */
  else if (VideoGraphicsMode == DisplayMode && VesaVideoMode)
    {
      BankSize = VesaVideoModeInformation.WindowGranularity << 10;
      BanksToCopy = (USHORT)((VesaVideoModeInformation.HeightInPixels * VesaVideoModeInformation.BytesPerScanLine) / BankSize);
      BytesInLastBank = (VesaVideoModeInformation.HeightInPixels * VesaVideoModeInformation.BytesPerScanLine) % BankSize;

      /* Copy all the banks but the last one because
       * it is probably a partial bank */
      for (CurrentBank = 0; CurrentBank < BanksToCopy; CurrentBank++)
        {
          PcVideoSetMemoryBank(CurrentBank);
          RtlCopyMemory((PVOID) VIDEOVGA_MEM_ADDRESS, (char *) Buffer + CurrentBank * BankSize, BankSize);
        }

      /* Copy the remaining bytes into the last bank */
      PcVideoSetMemoryBank(CurrentBank);
      RtlCopyMemory((PVOID)VIDEOVGA_MEM_ADDRESS, (char *) Buffer + CurrentBank * BankSize, BytesInLastBank);
    }
  /* BIOS graphics mode */
  else
    {
      UNIMPLEMENTED;
    }
}
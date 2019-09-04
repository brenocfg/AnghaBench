#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_6__ {int BasePage; scalar_t__ MemoryType; int PageCount; } ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PFREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 scalar_t__ ADDRESS_AND_SIZE_TO_SPAN_PAGES (scalar_t__,scalar_t__) ; 
 scalar_t__ ALIGN_UP_BY (int,int) ; 
 scalar_t__ AddMemoryDescriptor (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ DiskReadBuffer ; 
 int DiskReadBufferSize ; 
 int FREELDR_BASE ; 
 int FrLdrImageSize ; 
 scalar_t__ GetEbdaLocation (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetExtendedMemoryConfiguration (scalar_t__*,scalar_t__*) ; 
 scalar_t__ LoaderFirmwarePermanent ; 
 int /*<<< orphan*/  LoaderFirmwareTemporary ; 
 scalar_t__ LoaderFree ; 
 int /*<<< orphan*/  LoaderLoadedProgram ; 
 int /*<<< orphan*/  LoaderOsloaderStack ; 
 scalar_t__ LoaderSpecialMemory ; 
 int /*<<< orphan*/  MAX_BIOS_DESCRIPTORS ; 
 int /*<<< orphan*/  MAX_DISKREADBUFFER_SIZE ; 
 int /*<<< orphan*/  MmGetSystemMemoryMapTypeString (scalar_t__) ; 
 int PAGE_SIZE ; 
 scalar_t__ PcMapCount ; 
 int /*<<< orphan*/  PcMemCheckUsableMemorySize () ; 
 scalar_t__ PcMemGetBiosMemoryMap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PcMemGetConventionalMemorySize () ; 
 TYPE_1__* PcMemoryMap ; 
 int /*<<< orphan*/  ReserveMemory (int,int,int /*<<< orphan*/ ,char*) ; 
 int STACKADDR ; 
 int STACKLOW ; 
 int /*<<< orphan*/  SetMemory (int,int,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int min (int,int /*<<< orphan*/ ) ; 

PFREELDR_MEMORY_DESCRIPTOR
PcMemGetMemoryMap(ULONG *MemoryMapSize)
{
    ULONG i, EntryCount;
    ULONG ExtendedMemorySizeAtOneMB;
    ULONG ExtendedMemorySizeAtSixteenMB;
    ULONG EbdaBase, EbdaSize;

    TRACE("PcMemGetMemoryMap()\n");

    PcMemCheckUsableMemorySize();

    EntryCount = PcMemGetBiosMemoryMap(PcMemoryMap, MAX_BIOS_DESCRIPTORS);

    /* If the BIOS didn't provide a memory map, synthesize one */
    if (EntryCount == 0)
    {
        GetExtendedMemoryConfiguration(&ExtendedMemorySizeAtOneMB,
                                       &ExtendedMemorySizeAtSixteenMB);

        /* Conventional memory */
        AddMemoryDescriptor(PcMemoryMap,
                            MAX_BIOS_DESCRIPTORS,
                            0,
                            PcMemGetConventionalMemorySize() * 1024 / PAGE_SIZE,
                            LoaderFree);

        /* Extended memory */
        PcMapCount = AddMemoryDescriptor(PcMemoryMap,
                                         MAX_BIOS_DESCRIPTORS,
                                         1024 * 1024 / PAGE_SIZE,
                                         ExtendedMemorySizeAtOneMB * 1024 / PAGE_SIZE,
                                         LoaderFree);

        if (ExtendedMemorySizeAtSixteenMB != 0)
        {
            /* Extended memory at 16MB */
            PcMapCount = AddMemoryDescriptor(PcMemoryMap,
                                             MAX_BIOS_DESCRIPTORS,
                                             0x1000000 / PAGE_SIZE,
                                             ExtendedMemorySizeAtSixteenMB * 64 * 1024 / PAGE_SIZE,
                                             LoaderFree);
        }

        /* Check if we have an EBDA and get it's location */
        if (GetEbdaLocation(&EbdaBase, &EbdaSize))
        {
            /* Add the descriptor */
            PcMapCount = AddMemoryDescriptor(PcMemoryMap,
                                             MAX_BIOS_DESCRIPTORS,
                                             (EbdaBase / PAGE_SIZE),
                                             ADDRESS_AND_SIZE_TO_SPAN_PAGES(EbdaBase, EbdaSize),
                                             LoaderFirmwarePermanent);
        }
    }

    /* Setup some protected ranges */
    SetMemory(0x000000, 0x01000, LoaderFirmwarePermanent); // Realmode IVT / BDA
    SetMemory(0x0A0000, 0x50000, LoaderFirmwarePermanent); // Video memory
    SetMemory(0x0F0000, 0x10000, LoaderSpecialMemory); // ROM
    SetMemory(0xFFF000, 0x01000, LoaderSpecialMemory); // unusable memory (do we really need this?)

    /* Reserve some static ranges for freeldr */
    ReserveMemory(0x1000, STACKLOW - 0x1000, LoaderFirmwareTemporary, "BIOS area");
    ReserveMemory(STACKLOW, STACKADDR - STACKLOW, LoaderOsloaderStack, "FreeLdr stack");
    ReserveMemory(FREELDR_BASE, FrLdrImageSize, LoaderLoadedProgram, "FreeLdr image");

    /* Default to 1 page above freeldr for the disk read buffer */
    DiskReadBuffer = (PUCHAR)ALIGN_UP_BY(FREELDR_BASE + FrLdrImageSize, PAGE_SIZE);
    DiskReadBufferSize = PAGE_SIZE;

    /* Scan for free range above freeldr image */
    for (i = 0; i < PcMapCount; i++)
    {
        if ((PcMemoryMap[i].BasePage > (FREELDR_BASE / PAGE_SIZE)) &&
            (PcMemoryMap[i].MemoryType == LoaderFree))
        {
            /* Use this range for the disk read buffer */
            DiskReadBuffer = (PVOID)(PcMemoryMap[i].BasePage * PAGE_SIZE);
            DiskReadBufferSize = min(PcMemoryMap[i].PageCount * PAGE_SIZE,
                                     MAX_DISKREADBUFFER_SIZE);
            break;
        }
    }

    TRACE("DiskReadBuffer=0x%p, DiskReadBufferSize=0x%lx\n",
          DiskReadBuffer, DiskReadBufferSize);

    /* Now reserve the range for the disk read buffer */
    ReserveMemory((ULONG_PTR)DiskReadBuffer,
                  DiskReadBufferSize,
                  LoaderFirmwareTemporary,
                  "Disk read buffer");

    TRACE("Dumping resulting memory map:\n");
    for (i = 0; i < PcMapCount; i++)
    {
        TRACE("BasePage=0x%lx, PageCount=0x%lx, Type=%s\n",
              PcMemoryMap[i].BasePage,
              PcMemoryMap[i].PageCount,
              MmGetSystemMemoryMapTypeString(PcMemoryMap[i].MemoryType));
    }

    *MemoryMapSize = PcMapCount;
    return PcMemoryMap;
}
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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PFREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 scalar_t__ ADDRESS_AND_SIZE_TO_SPAN_PAGES (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AddMemoryDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetEbdaLocation (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetExtendedMemoryConfiguration (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  LoaderFirmwarePermanent ; 
 int /*<<< orphan*/  LoaderFree ; 
 int /*<<< orphan*/  LoaderSpecialMemory ; 
 int /*<<< orphan*/  MAX_BIOS_DESCRIPTORS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PcMapCount ; 
 int /*<<< orphan*/  PcMemCheckUsableMemorySize () ; 
 scalar_t__ PcMemFinalizeMemoryMap (int /*<<< orphan*/ ) ; 
 scalar_t__ PcMemGetBiosMemoryMap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PcMemGetConventionalMemorySize () ; 
 int /*<<< orphan*/  PcMemoryMap ; 
 int /*<<< orphan*/  SetMemory (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

PFREELDR_MEMORY_DESCRIPTOR
PcMemGetMemoryMap(ULONG *MemoryMapSize)
{
    ULONG EntryCount;
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
    SetMemory(PcMemoryMap, 0x000000, 0x01000, LoaderFirmwarePermanent); // Realmode IVT / BDA
    SetMemory(PcMemoryMap, 0x0A0000, 0x50000, LoaderFirmwarePermanent); // Video memory
    SetMemory(PcMemoryMap, 0x0F0000, 0x10000, LoaderSpecialMemory); // ROM
    SetMemory(PcMemoryMap, 0xFFF000, 0x01000, LoaderSpecialMemory); // unusable memory (do we really need this?)

    *MemoryMapSize = PcMemFinalizeMemoryMap(PcMemoryMap);
    return PcMemoryMap;
}
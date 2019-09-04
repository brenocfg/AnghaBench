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
typedef  int paddr_t ;
typedef  int ULONG ;
struct TYPE_3__ {int BaseAddress; int Length; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__* PBIOS_MEMORY_MAP ;

/* Variables and functions */
 int /*<<< orphan*/  BiosMemoryUsable ; 
 int GetPhys (int) ; 
 int /*<<< orphan*/  SetPhys (int,int) ; 
 int mem_range_end ; 
 int /*<<< orphan*/  printf (char*,int) ; 

ULONG PpcPrepGetMemoryMap( PBIOS_MEMORY_MAP BiosMemoryMap,
               ULONG MaxMemoryMapSize )
{
    // Probe memory
    paddr_t physAddr;
    register int oldStore = 0, newStore = 0, change = 0, oldmsr;

    __asm__("mfmsr %0\n" : "=r" (oldmsr));
    change = oldmsr & 0x6fff;
    __asm__("mtmsr %0\n" : : "r" (change));

    // Find the last ram address in physical space ... this bypasses mapping
    // but could run into non-ram objects right above ram.  Usually systems
    // aren't designed like that though.
    for (physAddr = 0x40000, change = newStore;
         (physAddr < 0x80000000) && (change == newStore);
         physAddr += 1 << 12)
    {
        oldStore = GetPhys(physAddr);
        newStore = (physAddr & 0x1000) ? 0x55aa55aa : 0xaa55aa55;
        SetPhys(physAddr, newStore);
        change = GetPhys(physAddr);
        SetPhys(physAddr, oldStore);
    }
    // Back off by one page
    physAddr -= 0x1000;
    BiosMemoryMap[0].BaseAddress = 0x30000; // End of ppcmmu
    BiosMemoryMap[0].Type = BiosMemoryUsable;
    BiosMemoryMap[0].Length = physAddr - BiosMemoryMap[0].BaseAddress;

    __asm__("mtmsr %0\n" : : "r" (oldmsr));

    mem_range_end = physAddr;

    printf("Actual RAM: %d Mb\n", physAddr >> 20);
    return 1;
}
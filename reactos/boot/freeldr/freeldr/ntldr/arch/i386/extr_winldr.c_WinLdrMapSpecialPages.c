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
struct TYPE_3__ {int Valid; int Write; void* PageFrameNumber; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* HalPageTable ; 
 int KIP0PCRADDRESS ; 
 int KI_USER_SHARED_DATA ; 
 int MM_PAGE_SHIFT ; 
 void* PcrBasePage ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WinLdrpMapApic () ; 

__attribute__((used)) static
BOOLEAN
WinLdrMapSpecialPages(void)
{
    TRACE("HalPageTable: 0x%X\n", HalPageTable);

    /*
     * The Page Tables have been setup, make special handling
     * for the boot processor PCR and KI_USER_SHARED_DATA.
     */
    HalPageTable[(KI_USER_SHARED_DATA - 0xFFC00000) >> MM_PAGE_SHIFT].PageFrameNumber = PcrBasePage+1;
    HalPageTable[(KI_USER_SHARED_DATA - 0xFFC00000) >> MM_PAGE_SHIFT].Valid = 1;
    HalPageTable[(KI_USER_SHARED_DATA - 0xFFC00000) >> MM_PAGE_SHIFT].Write = 1;

    HalPageTable[(KIP0PCRADDRESS - 0xFFC00000) >> MM_PAGE_SHIFT].PageFrameNumber = PcrBasePage;
    HalPageTable[(KIP0PCRADDRESS - 0xFFC00000) >> MM_PAGE_SHIFT].Valid = 1;
    HalPageTable[(KIP0PCRADDRESS - 0xFFC00000) >> MM_PAGE_SHIFT].Write = 1;

    /* Map APIC */
    WinLdrpMapApic();

    /* Map VGA memory */
    //VideoMemoryBase = MmMapIoSpace(0xb8000, 4000, MmNonCached);
    //TRACE("VideoMemoryBase: 0x%X\n", VideoMemoryBase);

    return TRUE;
}
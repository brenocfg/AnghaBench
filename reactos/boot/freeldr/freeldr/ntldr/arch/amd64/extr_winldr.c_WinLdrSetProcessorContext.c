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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG64 ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  KGDTENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Amd64SetupGdt (scalar_t__,int) ; 
 int /*<<< orphan*/  Amd64SetupIdt (scalar_t__) ; 
 scalar_t__ GdtIdt ; 
 int /*<<< orphan*/  KGDT64_SYS_TSS ; 
 int KSEG0_BASE ; 
 int MM_PAGE_SHIFT ; 
 int NUM_GDT ; 
 scalar_t__ PxeBase ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TssBasePage ; 
 int /*<<< orphan*/  __ltr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __writecr3 (scalar_t__) ; 
 int /*<<< orphan*/  __writeeflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _disable () ; 

VOID
WinLdrSetProcessorContext(void)
{
    TRACE("WinLdrSetProcessorContext\n");

    /* Disable Interrupts */
    _disable();

    /* Re-initialize EFLAGS */
    __writeeflags(0);

    /* Set the new PML4 */
    __writecr3((ULONG64)PxeBase);

    /* Get kernel mode address of gdt / idt */
    GdtIdt = (PVOID)((ULONG64)GdtIdt + KSEG0_BASE);

    /* Create gdt entries and load gdtr */
    Amd64SetupGdt(GdtIdt, KSEG0_BASE | (TssBasePage << MM_PAGE_SHIFT));

    /* Copy old Idt and set idtr */
    Amd64SetupIdt((PVOID)((ULONG64)GdtIdt + NUM_GDT * sizeof(KGDTENTRY)));

    /* LDT is unused */
//    __lldt(0);

    /* Load TSR */
    __ltr(KGDT64_SYS_TSS);

    TRACE("leave WinLdrSetProcessorContext\n");
}
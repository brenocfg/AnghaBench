#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  void* USHORT ;
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  void* UCHAR ;
struct TYPE_12__ {int Base; int Limit; } ;
struct TYPE_9__ {int BaseMid; int Flags1; int Flags2; int BaseHi; } ;
struct TYPE_10__ {TYPE_1__ Bytes; } ;
struct TYPE_11__ {int LimitLow; int BaseLow; TYPE_2__ HighWord; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  scalar_t__ PKIDTENTRY ;
typedef  TYPE_3__* PKGDTENTRY ;
typedef  int /*<<< orphan*/  KIDTENTRY ;
typedef  int /*<<< orphan*/  KGDTENTRY ;
typedef  TYPE_4__ GDTIDT ;

/* Variables and functions */
 int CR0_PG ; 
 scalar_t__ GdtIdt ; 
 int /*<<< orphan*/  KGDT_TSS ; 
 int KIP0PCRADDRESS ; 
 int KSEG0_BASE ; 
 int /*<<< orphan*/  Ke386GetGlobalDescriptorTable (TYPE_4__*) ; 
 int /*<<< orphan*/  Ke386SetDs (int) ; 
 int /*<<< orphan*/  Ke386SetEs (int) ; 
 int /*<<< orphan*/  Ke386SetFs (int) ; 
 int /*<<< orphan*/  Ke386SetGlobalDescriptorTable (TYPE_4__*) ; 
 int /*<<< orphan*/  Ke386SetGs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ke386SetLocalDescriptorTable (void*) ; 
 int /*<<< orphan*/  Ke386SetSs (int) ; 
 int /*<<< orphan*/  Ke386SetTr (int /*<<< orphan*/ ) ; 
 int MM_PAGE_SHIFT ; 
 int /*<<< orphan*/  MM_PAGE_SIZE ; 
 int NUM_GDT ; 
 int NUM_IDT ; 
 scalar_t__ PDE ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int) ; 
 int TssBasePage ; 
 int /*<<< orphan*/  __lidt (TYPE_4__*) ; 
 int __readcr0 () ; 
 int /*<<< orphan*/  __sidt (TYPE_4__*) ; 
 int /*<<< orphan*/  __writecr0 (int) ; 
 int /*<<< orphan*/  __writecr3 (int) ; 
 int /*<<< orphan*/  __writeeflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _disable () ; 

VOID
WinLdrSetProcessorContext(void)
{
    GDTIDT GdtDesc, IdtDesc, OldIdt;
    PKGDTENTRY    pGdt;
    PKIDTENTRY    pIdt;
    USHORT Ldt = 0;
    ULONG Pcr;
    ULONG Tss;
    //ULONG i;

    Pcr = KIP0PCRADDRESS;
    Tss = KSEG0_BASE | (TssBasePage << MM_PAGE_SHIFT);

    TRACE("GDtIdt %p, Pcr %p, Tss 0x%08X\n",
        GdtIdt, Pcr, Tss);

    // Enable paging
    //BS->ExitBootServices(ImageHandle,MapKey);

    // Disable Interrupts
    _disable();

    // Re-initialize EFLAGS
    __writeeflags(0);

    // Set the PDBR
    __writecr3((ULONG_PTR)PDE);

    // Enable paging by modifying CR0
    __writecr0(__readcr0() | CR0_PG);

    // Kernel expects the PCR to be zero-filled on startup
    // FIXME: Why zero it here when we can zero it right after allocation?
    RtlZeroMemory((PVOID)Pcr, MM_PAGE_SIZE); //FIXME: Why zero only 1 page when we allocate 2?

    // Get old values of GDT and IDT
    Ke386GetGlobalDescriptorTable(&GdtDesc);
    __sidt(&IdtDesc);

    // Save old IDT
    OldIdt.Base = IdtDesc.Base;
    OldIdt.Limit = IdtDesc.Limit;

    // Prepare new IDT+GDT
    GdtDesc.Base  = KSEG0_BASE | (ULONG_PTR)GdtIdt;
    GdtDesc.Limit = NUM_GDT * sizeof(KGDTENTRY) - 1;
    IdtDesc.Base  = (ULONG)((PUCHAR)GdtDesc.Base + GdtDesc.Limit + 1);
    IdtDesc.Limit = NUM_IDT * sizeof(KIDTENTRY) - 1;

    // ========================
    // Fill all descriptors now
    // ========================

    pGdt = (PKGDTENTRY)GdtDesc.Base;
    pIdt = (PKIDTENTRY)IdtDesc.Base;

    //
    // Code selector (0x8)
    // Flat 4Gb
    //
    pGdt[1].LimitLow                = 0xFFFF;
    pGdt[1].BaseLow                    = 0;
    pGdt[1].HighWord.Bytes.BaseMid    = 0;
    pGdt[1].HighWord.Bytes.Flags1    = 0x9A;
    pGdt[1].HighWord.Bytes.Flags2    = 0xCF;
    pGdt[1].HighWord.Bytes.BaseHi    = 0;

    //
    // Data selector (0x10)
    // Flat 4Gb
    //
    pGdt[2].LimitLow                = 0xFFFF;
    pGdt[2].BaseLow                    = 0;
    pGdt[2].HighWord.Bytes.BaseMid    = 0;
    pGdt[2].HighWord.Bytes.Flags1    = 0x92;
    pGdt[2].HighWord.Bytes.Flags2    = 0xCF;
    pGdt[2].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x18)
    // Flat 2Gb
    //
    pGdt[3].LimitLow                = 0xFFFF;
    pGdt[3].BaseLow                    = 0;
    pGdt[3].HighWord.Bytes.BaseMid    = 0;
    pGdt[3].HighWord.Bytes.Flags1    = 0xFA;
    pGdt[3].HighWord.Bytes.Flags2    = 0xCF;
    pGdt[3].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x20)
    // Flat 2Gb
    //
    pGdt[4].LimitLow                = 0xFFFF;
    pGdt[4].BaseLow                    = 0;
    pGdt[4].HighWord.Bytes.BaseMid    = 0;
    pGdt[4].HighWord.Bytes.Flags1    = 0xF2;
    pGdt[4].HighWord.Bytes.Flags2    = 0xCF;
    pGdt[4].HighWord.Bytes.BaseHi    = 0;

    //
    // TSS Selector (0x28)
    //
    pGdt[5].LimitLow                = 0x78-1; //FIXME: Check this
    pGdt[5].BaseLow = (USHORT)(Tss & 0xffff);
    pGdt[5].HighWord.Bytes.BaseMid = (UCHAR)((Tss >> 16) & 0xff);
    pGdt[5].HighWord.Bytes.Flags1    = 0x89;
    pGdt[5].HighWord.Bytes.Flags2    = 0x00;
    pGdt[5].HighWord.Bytes.BaseHi  = (UCHAR)((Tss >> 24) & 0xff);

    //
    // PCR Selector (0x30)
    //
    pGdt[6].LimitLow                = 0x01;
    pGdt[6].BaseLow  = (USHORT)(Pcr & 0xffff);
    pGdt[6].HighWord.Bytes.BaseMid = (UCHAR)((Pcr >> 16) & 0xff);
    pGdt[6].HighWord.Bytes.Flags1    = 0x92;
    pGdt[6].HighWord.Bytes.Flags2    = 0xC0;
    pGdt[6].HighWord.Bytes.BaseHi  = (UCHAR)((Pcr >> 24) & 0xff);

    //
    // Selector (0x38)
    //
    pGdt[7].LimitLow                = 0xFFFF;
    pGdt[7].BaseLow                    = 0;
    pGdt[7].HighWord.Bytes.BaseMid    = 0;
    pGdt[7].HighWord.Bytes.Flags1    = 0xF3;
    pGdt[7].HighWord.Bytes.Flags2    = 0x40;
    pGdt[7].HighWord.Bytes.BaseHi    = 0;

    //
    // Some BIOS stuff (0x40)
    //
    pGdt[8].LimitLow                = 0xFFFF;
    pGdt[8].BaseLow                    = 0x400;
    pGdt[8].HighWord.Bytes.BaseMid    = 0;
    pGdt[8].HighWord.Bytes.Flags1    = 0xF2;
    pGdt[8].HighWord.Bytes.Flags2    = 0x0;
    pGdt[8].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x48)
    //
    pGdt[9].LimitLow                = 0;
    pGdt[9].BaseLow                    = 0;
    pGdt[9].HighWord.Bytes.BaseMid    = 0;
    pGdt[9].HighWord.Bytes.Flags1    = 0;
    pGdt[9].HighWord.Bytes.Flags2    = 0;
    pGdt[9].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x50)
    //
    pGdt[10].LimitLow                = 0xFFFF; //FIXME: Not correct!
    pGdt[10].BaseLow                = 0;
    pGdt[10].HighWord.Bytes.BaseMid    = 0x2;
    pGdt[10].HighWord.Bytes.Flags1    = 0x89;
    pGdt[10].HighWord.Bytes.Flags2    = 0;
    pGdt[10].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x58)
    //
    pGdt[11].LimitLow                = 0xFFFF;
    pGdt[11].BaseLow                = 0;
    pGdt[11].HighWord.Bytes.BaseMid    = 0x2;
    pGdt[11].HighWord.Bytes.Flags1    = 0x9A;
    pGdt[11].HighWord.Bytes.Flags2    = 0;
    pGdt[11].HighWord.Bytes.BaseHi    = 0;

    //
    // Selector (0x60)
    //
    pGdt[12].LimitLow                = 0xFFFF;
    pGdt[12].BaseLow                = 0; //FIXME: Maybe not correct, but noone cares
    pGdt[12].HighWord.Bytes.BaseMid    = 0x2;
    pGdt[12].HighWord.Bytes.Flags1    = 0x92;
    pGdt[12].HighWord.Bytes.Flags2    = 0;
    pGdt[12].HighWord.Bytes.BaseHi    = 0;

    //
    // Video buffer Selector (0x68)
    //
    pGdt[13].LimitLow                = 0x3FFF;
    pGdt[13].BaseLow                = 0x8000;
    pGdt[13].HighWord.Bytes.BaseMid    = 0x0B;
    pGdt[13].HighWord.Bytes.Flags1    = 0x92;
    pGdt[13].HighWord.Bytes.Flags2    = 0;
    pGdt[13].HighWord.Bytes.BaseHi    = 0;

    //
    // Points to GDT (0x70)
    //
    pGdt[14].LimitLow                = NUM_GDT*sizeof(KGDTENTRY) - 1;
    pGdt[14].BaseLow                = 0x7000;
    pGdt[14].HighWord.Bytes.BaseMid    = 0xFF;
    pGdt[14].HighWord.Bytes.Flags1    = 0x92;
    pGdt[14].HighWord.Bytes.Flags2    = 0;
    pGdt[14].HighWord.Bytes.BaseHi    = 0xFF;

    //
    // Some unused descriptors should go here
    //

    // Copy the old IDT
    RtlCopyMemory(pIdt, (PVOID)OldIdt.Base, OldIdt.Limit + 1);

    // Mask interrupts
    //asm("cli\n"); // they are already masked before enabling paged mode

    // Load GDT+IDT
    Ke386SetGlobalDescriptorTable(&GdtDesc);
    __lidt(&IdtDesc);

    // Jump to proper CS and clear prefetch queue
#if defined(__GNUC__)
    asm("ljmp    $0x08, $1f\n"
        "1:\n");
#elif defined(_MSC_VER)
    /* We can't express the above in MASM so we use this far return instead */
    __asm
    {
        push 8
        push offset resume
        retf
        resume:
    };
#else
#error
#endif

    // Set SS selector
    Ke386SetSs(0x10); // DataSelector=0x10

    // Set DS and ES selectors
    Ke386SetDs(0x10);
    Ke386SetEs(0x10); // this is vital for rep stosd

    // LDT = not used ever, thus set to 0
    Ke386SetLocalDescriptorTable(Ldt);

    // Load TSR
    Ke386SetTr(KGDT_TSS);

    // Clear GS
    Ke386SetGs(0);

    // Set FS to PCR
    Ke386SetFs(0x30);

        // Real end of the function, just for information
        /* do not uncomment!
        pop edi;
        pop esi;
        pop ebx;
        mov esp, ebp;
        pop ebp;
        ret
        */
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_20__ {scalar_t__ EntryPoint; } ;
struct TYPE_19__ {TYPE_1__* Extension; int /*<<< orphan*/  ConfigurationRoot; } ;
struct TYPE_18__ {int /*<<< orphan*/  LoaderPagesSpanned; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PLOADER_PARAMETER_BLOCK ;
typedef  TYPE_3__* PLDR_DATA_TABLE_ENTRY ;
typedef  scalar_t__ PCSTR ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  (* KERNEL_ENTRY_POINT ) (TYPE_2__*) ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOEXEC ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  IniCleanup () ; 
 scalar_t__ KI_USER_SHARED_DATA ; 
 scalar_t__ LoadWindowsCore (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__,TYPE_3__**) ; 
 int /*<<< orphan*/  LoaderPagesSpanned ; 
 int /*<<< orphan*/  MM_PAGE_SIZE ; 
 int /*<<< orphan*/  MachHwDetect () ; 
 int /*<<< orphan*/  MachPrepareForReactOS () ; 
 TYPE_2__* PaToVa (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  UiDrawBackdrop () ; 
 int /*<<< orphan*/  UiDrawProgressBarCenter (int,int,char*) ; 
 int /*<<< orphan*/  UiMessageBox (char*) ; 
 int /*<<< orphan*/  WinLdrInitializePhase1 (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WinLdrLoadBootDrivers (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  WinLdrSetProcessorContext () ; 
 int /*<<< orphan*/  WinLdrSetupEms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinLdrSetupMachineDependent (TYPE_2__*) ; 
 int /*<<< orphan*/  WinLdrSetupMemoryLayout (TYPE_2__*) ; 
 int /*<<< orphan*/  WinLdrpDumpArcDisks (TYPE_2__*) ; 
 int /*<<< orphan*/  WinLdrpDumpBootDriver (TYPE_2__*) ; 
 int /*<<< orphan*/  WinLdrpDumpMemoryDescriptors (TYPE_2__*) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

ARC_STATUS
LoadAndBootWindowsCommon(
    USHORT OperatingSystemVersion,
    PLOADER_PARAMETER_BLOCK LoaderBlock,
    PCSTR BootOptions,
    PCSTR BootPath,
    BOOLEAN Setup)
{
    PLOADER_PARAMETER_BLOCK LoaderBlockVA;
    BOOLEAN Success;
    PLDR_DATA_TABLE_ENTRY KernelDTE;
    KERNEL_ENTRY_POINT KiSystemStartup;
    PCSTR SystemRoot;

    TRACE("LoadAndBootWindowsCommon()\n");

    ASSERT(OperatingSystemVersion != 0);

#ifdef _M_IX86
    /* Setup redirection support */
    WinLdrSetupEms((PCHAR)BootOptions);
#endif

    /* Convert BootPath to SystemRoot */
    SystemRoot = strstr(BootPath, "\\");

    /* Detect hardware */
    UiDrawBackdrop();
    UiDrawProgressBarCenter(20, 100, "Detecting hardware...");
    LoaderBlock->ConfigurationRoot = MachHwDetect();

    /* Load the operating system core: the Kernel, the HAL and the Kernel Debugger Transport DLL */
    Success = LoadWindowsCore(OperatingSystemVersion,
                              LoaderBlock,
                              BootOptions,
                              BootPath,
                              &KernelDTE);
    if (!Success)
    {
        UiMessageBox("Error loading NTOS core.");
        return ENOEXEC;
    }

    /* Load boot drivers */
    UiDrawBackdrop();
    UiDrawProgressBarCenter(100, 100, "Loading boot drivers...");
    Success = WinLdrLoadBootDrivers(LoaderBlock, BootPath);
    TRACE("Boot drivers loading %s\n", Success ? "successful" : "failed");

    /* Cleanup ini file */
    IniCleanup();

    /* Initialize Phase 1 - no drivers loading anymore */
    WinLdrInitializePhase1(LoaderBlock,
                           BootOptions,
                           SystemRoot,
                           BootPath,
                           OperatingSystemVersion);

    /* Save entry-point pointer and Loader block VAs */
    KiSystemStartup = (KERNEL_ENTRY_POINT)KernelDTE->EntryPoint;
    LoaderBlockVA = PaToVa(LoaderBlock);

    /* "Stop all motors", change videomode */
    MachPrepareForReactOS();

    /* Debugging... */
    //DumpMemoryAllocMap();

    /* Do the machine specific initialization */
    WinLdrSetupMachineDependent(LoaderBlock);

    /* Map pages and create memory descriptors */
    WinLdrSetupMemoryLayout(LoaderBlock);

    /* Set processor context */
    WinLdrSetProcessorContext();

    /* Save final value of LoaderPagesSpanned */
    LoaderBlock->Extension->LoaderPagesSpanned = LoaderPagesSpanned;

    TRACE("Hello from paged mode, KiSystemStartup %p, LoaderBlockVA %p!\n",
          KiSystemStartup, LoaderBlockVA);

    /* Zero KI_USER_SHARED_DATA page */
    RtlZeroMemory((PVOID)KI_USER_SHARED_DATA, MM_PAGE_SIZE);

    WinLdrpDumpMemoryDescriptors(LoaderBlockVA);
    WinLdrpDumpBootDriver(LoaderBlockVA);
#ifndef _M_AMD64
    WinLdrpDumpArcDisks(LoaderBlockVA);
#endif

    /* Pass control */
    (*KiSystemStartup)(LoaderBlockVA);
    return ESUCCESS;
}
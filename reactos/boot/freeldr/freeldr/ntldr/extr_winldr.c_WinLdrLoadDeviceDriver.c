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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_1__* PLDR_DATA_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  FullPath ;
typedef  int /*<<< orphan*/  DriverPath ;
typedef  int /*<<< orphan*/  DllName ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_NULL ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LoaderBootDriver ; 
 scalar_t__ PeLdrAllocateDataTableEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ PeLdrCheckForLoadedDll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ PeLdrLoadImage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PeLdrScanImportDescriptorTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlStringCbCopyA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlStringCbPrintfA (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * strrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static BOOLEAN
WinLdrLoadDeviceDriver(PLIST_ENTRY LoadOrderListHead,
                       PCSTR BootPath,
                       PUNICODE_STRING FilePath,
                       ULONG Flags,
                       PLDR_DATA_TABLE_ENTRY *DriverDTE)
{
    CHAR FullPath[1024];
    CHAR DriverPath[1024];
    CHAR DllName[1024];
    PCHAR DriverNamePos;
    BOOLEAN Success;
    PVOID DriverBase = NULL;

    // Separate the path to file name and directory path
    RtlStringCbPrintfA(DriverPath, sizeof(DriverPath), "%wZ", FilePath);
    DriverNamePos = strrchr(DriverPath, '\\');
    if (DriverNamePos != NULL)
    {
        // Copy the name
        RtlStringCbCopyA(DllName, sizeof(DllName), DriverNamePos+1);

        // Cut out the name from the path
        *(DriverNamePos+1) = ANSI_NULL;
    }
    else
    {
        // There is no directory in the path
        RtlStringCbCopyA(DllName, sizeof(DllName), DriverPath);
        *DriverPath = ANSI_NULL;
    }

    TRACE("DriverPath: '%s', DllName: '%s', LPB\n", DriverPath, DllName);

    // Check if driver is already loaded
    Success = PeLdrCheckForLoadedDll(LoadOrderListHead, DllName, DriverDTE);
    if (Success)
    {
        // We've got the pointer to its DTE, just return success
        return TRUE;
    }

    // It's not loaded, we have to load it
    RtlStringCbPrintfA(FullPath, sizeof(FullPath), "%s%wZ", BootPath, FilePath);
    Success = PeLdrLoadImage(FullPath, LoaderBootDriver, &DriverBase);
    if (!Success)
        return FALSE;

    // Allocate a DTE for it
    Success = PeLdrAllocateDataTableEntry(LoadOrderListHead, DllName, DllName, DriverBase, DriverDTE);
    if (!Success)
    {
        ERR("PeLdrAllocateDataTableEntry() failed\n");
        return FALSE;
    }

    // Modify any flags, if needed
    (*DriverDTE)->Flags |= Flags;

    // Look for any dependencies it may have, and load them too
    RtlStringCbPrintfA(FullPath, sizeof(FullPath), "%s%s", BootPath, DriverPath);
    Success = PeLdrScanImportDescriptorTable(LoadOrderListHead, FullPath, *DriverDTE);
    if (!Success)
    {
        ERR("PeLdrScanImportDescriptorTable() failed for %s\n", FullPath);
        return FALSE;
    }

    return TRUE;
}
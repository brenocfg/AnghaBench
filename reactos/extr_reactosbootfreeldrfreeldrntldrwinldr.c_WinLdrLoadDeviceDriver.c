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
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_1__* PLDR_DATA_TABLE_ENTRY ;
typedef  scalar_t__* PCHAR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  FullPath ;
typedef  int /*<<< orphan*/  DriverPath ;
typedef  scalar_t__ CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ ANSI_NULL ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LoaderBootDriver ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WinLdrAllocateDataTableEntry (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ WinLdrCheckForLoadedDll (int /*<<< orphan*/ ,scalar_t__*,TYPE_1__**) ; 
 scalar_t__ WinLdrLoadImage (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ WinLdrScanImportDescriptorTable (int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _snprintf (scalar_t__*,int,char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__*) ; 
 scalar_t__* strrchr (scalar_t__*,char) ; 

__attribute__((used)) static BOOLEAN
WinLdrLoadDeviceDriver(PLIST_ENTRY LoadOrderListHead,
                       LPCSTR BootPath,
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
    _snprintf(DriverPath, sizeof(DriverPath), "%wZ", FilePath);
    DriverNamePos = strrchr(DriverPath, '\\');
    if (DriverNamePos != NULL)
    {
        // Copy the name
        strcpy(DllName, DriverNamePos+1);

        // Cut out the name from the path
        *(DriverNamePos+1) = 0;
    }
    else
    {
        // There is no directory in the path
        strcpy(DllName, DriverPath);
        DriverPath[0] = ANSI_NULL;
    }

    TRACE("DriverPath: %s, DllName: %s, LPB\n", DriverPath, DllName);

    // Check if driver is already loaded
    Success = WinLdrCheckForLoadedDll(LoadOrderListHead, DllName, DriverDTE);
    if (Success)
    {
        // We've got the pointer to its DTE, just return success
        return TRUE;
    }

    // It's not loaded, we have to load it
    _snprintf(FullPath, sizeof(FullPath), "%s%wZ", BootPath, FilePath);
    Success = WinLdrLoadImage(FullPath, LoaderBootDriver, &DriverBase);
    if (!Success)
        return FALSE;

    // Allocate a DTE for it
    Success = WinLdrAllocateDataTableEntry(LoadOrderListHead, DllName, DllName, DriverBase, DriverDTE);
    if (!Success)
    {
        ERR("WinLdrAllocateDataTableEntry() failed\n");
        return FALSE;
    }

    // Modify any flags, if needed
    (*DriverDTE)->Flags |= Flags;

    // Look for any dependencies it may have, and load them too
    sprintf(FullPath,"%s%s", BootPath, DriverPath);
    Success = WinLdrScanImportDescriptorTable(LoadOrderListHead, FullPath, *DriverDTE);
    if (!Success)
    {
        ERR("WinLdrScanImportDescriptorTable() failed for %s\n", FullPath);
        return FALSE;
    }

    return TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_7__ {TYPE_1__ BaseDllName; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_2__* PLDR_DATA_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  PCH ;
typedef  int /*<<< orphan*/  PCCH ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  LoaderBootDriver ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * VaToPa (int /*<<< orphan*/ ) ; 
 scalar_t__ WinLdrAllocateDataTableEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ WinLdrLoadImage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ WinLdrScanImportDescriptorTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
WinLdrpLoadAndScanReferencedDll(PLIST_ENTRY ModuleListHead,
                                PCCH DirectoryPath,
                                PCH ImportName,
                                PLDR_DATA_TABLE_ENTRY *DataTableEntry)
{
    CHAR FullDllName[256];
    BOOLEAN Success;
    PVOID BasePA = NULL;

    /* Prepare the full path to the file to be loaded */
    strcpy(FullDllName, DirectoryPath);
    strcat(FullDllName, ImportName);

    TRACE("Loading referenced DLL: %s\n", FullDllName);
    //Print(L"Loading referenced DLL: %s\n", FullDllName);

    /* Load the image */
    Success = WinLdrLoadImage(FullDllName, LoaderBootDriver, &BasePA);
    if (!Success)
    {
        ERR("WinLdrLoadImage() failed\n");
        return Success;
    }

    /* Allocate DTE for newly loaded DLL */
    Success = WinLdrAllocateDataTableEntry(ModuleListHead,
                                           ImportName,
                                           FullDllName,
                                           BasePA,
                                           DataTableEntry);
    if (!Success)
    {
        ERR("WinLdrAllocateDataTableEntry() failed\n");
        return Success;
    }

    /* Scan its dependencies too */
    TRACE("WinLdrScanImportDescriptorTable() calling ourselves for %S\n",
        VaToPa((*DataTableEntry)->BaseDllName.Buffer));
    Success = WinLdrScanImportDescriptorTable(ModuleListHead, DirectoryPath, *DataTableEntry);
    if (!Success)
    {
        ERR("WinLdrScanImportDescriptorTable() failed\n");
        return Success;
    }

    return TRUE;
}
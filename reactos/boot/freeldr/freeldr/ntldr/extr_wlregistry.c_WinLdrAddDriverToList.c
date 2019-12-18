#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
typedef  int /*<<< orphan*/  UNICODE_NULL ;
struct TYPE_6__ {int MaximumLength; TYPE_1__* Buffer; scalar_t__ Length; } ;
struct TYPE_5__ {TYPE_2__ RegistryPath; TYPE_2__ FilePath; int /*<<< orphan*/ * LdrEntry; } ;
typedef  scalar_t__* PWSTR ;
typedef  TYPE_1__* PBOOT_DRIVER_LIST_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  int /*<<< orphan*/  BOOT_DRIVER_LIST_ENTRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* FrLdrHeapAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrHeapFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertInBootDriverList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAppendUnicodeToString (TYPE_2__*,...) ; 
 int /*<<< orphan*/  TAG_WLDR_BDE ; 
 int /*<<< orphan*/  TAG_WLDR_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ wcslen (scalar_t__*) ; 

BOOLEAN
WinLdrAddDriverToList(LIST_ENTRY *BootDriverListHead,
                      PWSTR RegistryPath,
                      PWSTR ImagePath,
                      PWSTR ServiceName)
{
    PBOOT_DRIVER_LIST_ENTRY BootDriverEntry;
    NTSTATUS Status;
    USHORT PathLength;

    BootDriverEntry = FrLdrHeapAlloc(sizeof(BOOT_DRIVER_LIST_ENTRY), TAG_WLDR_BDE);

    if (!BootDriverEntry)
        return FALSE;

    // DTE will be filled during actual load of the driver
    BootDriverEntry->LdrEntry = NULL;

    // Check - if we have a valid ImagePath, if not - we need to build it
    // like "System32\\Drivers\\blah.sys"
    if (ImagePath && (ImagePath[0] != 0))
    {
        // Just copy ImagePath to the corresponding field in the structure
        PathLength = (USHORT)wcslen(ImagePath) * sizeof(WCHAR) + sizeof(UNICODE_NULL);

        BootDriverEntry->FilePath.Length = 0;
        BootDriverEntry->FilePath.MaximumLength = PathLength;
        BootDriverEntry->FilePath.Buffer = FrLdrHeapAlloc(PathLength, TAG_WLDR_NAME);

        if (!BootDriverEntry->FilePath.Buffer)
        {
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_BDE);
            return FALSE;
        }

        Status = RtlAppendUnicodeToString(&BootDriverEntry->FilePath, ImagePath);
        if (!NT_SUCCESS(Status))
        {
            FrLdrHeapFree(BootDriverEntry->FilePath.Buffer, TAG_WLDR_NAME);
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_BDE);
            return FALSE;
        }
    }
    else
    {
        // we have to construct ImagePath ourselves
        PathLength = (USHORT)wcslen(ServiceName)*sizeof(WCHAR) + sizeof(L"system32\\drivers\\.sys");
        BootDriverEntry->FilePath.Length = 0;
        BootDriverEntry->FilePath.MaximumLength = PathLength;
        BootDriverEntry->FilePath.Buffer = FrLdrHeapAlloc(PathLength, TAG_WLDR_NAME);

        if (!BootDriverEntry->FilePath.Buffer)
        {
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_NAME);
            return FALSE;
        }

        Status = RtlAppendUnicodeToString(&BootDriverEntry->FilePath, L"system32\\drivers\\");
        if (!NT_SUCCESS(Status))
        {
            FrLdrHeapFree(BootDriverEntry->FilePath.Buffer, TAG_WLDR_NAME);
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_NAME);
            return FALSE;
        }

        Status = RtlAppendUnicodeToString(&BootDriverEntry->FilePath, ServiceName);
        if (!NT_SUCCESS(Status))
        {
            FrLdrHeapFree(BootDriverEntry->FilePath.Buffer, TAG_WLDR_NAME);
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_NAME);
            return FALSE;
        }

        Status = RtlAppendUnicodeToString(&BootDriverEntry->FilePath, L".sys");
        if (!NT_SUCCESS(Status))
        {
            FrLdrHeapFree(BootDriverEntry->FilePath.Buffer, TAG_WLDR_NAME);
            FrLdrHeapFree(BootDriverEntry, TAG_WLDR_NAME);
            return FALSE;
        }
    }

    // Add registry path
    PathLength = (USHORT)(wcslen(RegistryPath) + wcslen(ServiceName))*sizeof(WCHAR) + sizeof(UNICODE_NULL);
    BootDriverEntry->RegistryPath.Length = 0;
    BootDriverEntry->RegistryPath.MaximumLength = PathLength;
    BootDriverEntry->RegistryPath.Buffer = FrLdrHeapAlloc(PathLength, TAG_WLDR_NAME);
    if (!BootDriverEntry->RegistryPath.Buffer)
        return FALSE;

    Status = RtlAppendUnicodeToString(&BootDriverEntry->RegistryPath, RegistryPath);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Status = RtlAppendUnicodeToString(&BootDriverEntry->RegistryPath, ServiceName);
    if (!NT_SUCCESS(Status))
        return FALSE;

    // Insert entry into the list
    if (!InsertInBootDriverList(BootDriverListHead, BootDriverEntry))
    {
        // It was already there, so delete our entry
        if (BootDriverEntry->FilePath.Buffer) FrLdrHeapFree(BootDriverEntry->FilePath.Buffer, TAG_WLDR_NAME);
        if (BootDriverEntry->RegistryPath.Buffer) FrLdrHeapFree(BootDriverEntry->RegistryPath.Buffer, TAG_WLDR_NAME);
        FrLdrHeapFree(BootDriverEntry, TAG_WLDR_BDE);
    }

    return TRUE;
}
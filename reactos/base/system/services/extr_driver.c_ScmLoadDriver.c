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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int /*<<< orphan*/  lpServiceName; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PSERVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtLoadDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlAdjustPrivilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_LOAD_DRIVER_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
DWORD
ScmLoadDriver(PSERVICE lpService)
{
    NTSTATUS Status = STATUS_SUCCESS;
    BOOLEAN WasPrivilegeEnabled = FALSE;
    PWSTR pszDriverPath;
    UNICODE_STRING DriverPath;

    /* Build the driver path */
    /* 52 = wcslen(L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\") */
    pszDriverPath = HeapAlloc(GetProcessHeap(),
                              HEAP_ZERO_MEMORY,
                              (52 + wcslen(lpService->lpServiceName) + 1) * sizeof(WCHAR));
    if (pszDriverPath == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    wcscpy(pszDriverPath,
           L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\");
    wcscat(pszDriverPath,
           lpService->lpServiceName);

    RtlInitUnicodeString(&DriverPath,
                         pszDriverPath);

    DPRINT("  Path: %wZ\n", &DriverPath);

    /* Acquire driver-loading privilege */
    Status = RtlAdjustPrivilege(SE_LOAD_DRIVER_PRIVILEGE,
                                TRUE,
                                FALSE,
                                &WasPrivilegeEnabled);
    if (!NT_SUCCESS(Status))
    {
        /* We encountered a failure, exit properly */
        DPRINT1("SERVICES: Cannot acquire driver-loading privilege, Status = 0x%08lx\n", Status);
        goto done;
    }

    Status = NtLoadDriver(&DriverPath);

    /* Release driver-loading privilege */
    RtlAdjustPrivilege(SE_LOAD_DRIVER_PRIVILEGE,
                       WasPrivilegeEnabled,
                       FALSE,
                       &WasPrivilegeEnabled);

done:
    HeapFree(GetProcessHeap(), 0, pszDriverPath);
    return RtlNtStatusToDosError(Status);
}
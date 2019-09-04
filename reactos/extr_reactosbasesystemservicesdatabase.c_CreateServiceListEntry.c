#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwServiceType; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpImage; int /*<<< orphan*/ * pSecurityDescriptor; TYPE_2__ Status; int /*<<< orphan*/  bDeleted; scalar_t__ dwErrorControl; scalar_t__ dwTag; int /*<<< orphan*/  dwStartType; TYPE_1__* lpGroup; int /*<<< orphan*/  lpServiceName; int /*<<< orphan*/ * lpDisplayName; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpGroupName; } ;
typedef  TYPE_3__* PSERVICE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ SERVICE_FILE_SYSTEM_DRIVER ; 
 scalar_t__ SERVICE_INTERACTIVE_PROCESS ; 
 scalar_t__ SERVICE_KERNEL_DRIVER ; 
 int SERVICE_WIN32 ; 
 scalar_t__ SERVICE_WIN32_OWN_PROCESS ; 
 scalar_t__ SERVICE_WIN32_SHARE_PROCESS ; 
 scalar_t__ ScmCreateDefaultServiceSD (int /*<<< orphan*/ **) ; 
 scalar_t__ ScmCreateNewServiceRecord (int*,TYPE_3__**,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ScmGenerateServiceTag (TYPE_3__*) ; 
 scalar_t__ ScmIsDeleteFlagSet (int /*<<< orphan*/ ) ; 
 scalar_t__ ScmReadSecurityDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ScmReadString (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ ScmSetServiceGroup (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ScmWriteSecurityDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static DWORD
CreateServiceListEntry(LPCWSTR lpServiceName,
                       HKEY hServiceKey)
{
    PSERVICE lpService = NULL;
    LPWSTR lpDisplayName = NULL;
    LPWSTR lpGroup = NULL;
    DWORD dwSize;
    DWORD dwError;
    DWORD dwServiceType;
    DWORD dwStartType;
    DWORD dwErrorControl;
    DWORD dwTagId;

    DPRINT("Service: '%S'\n", lpServiceName);
    if (*lpServiceName == L'{')
        return ERROR_SUCCESS;

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hServiceKey,
                               L"Type",
                               NULL,
                               NULL,
                               (LPBYTE)&dwServiceType,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    if (((dwServiceType & ~SERVICE_INTERACTIVE_PROCESS) != SERVICE_WIN32_OWN_PROCESS) &&
        ((dwServiceType & ~SERVICE_INTERACTIVE_PROCESS) != SERVICE_WIN32_SHARE_PROCESS) &&
        (dwServiceType != SERVICE_KERNEL_DRIVER) &&
        (dwServiceType != SERVICE_FILE_SYSTEM_DRIVER))
        return ERROR_SUCCESS;

    DPRINT("Service type: %lx\n", dwServiceType);

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hServiceKey,
                               L"Start",
                               NULL,
                               NULL,
                               (LPBYTE)&dwStartType,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    DPRINT("Start type: %lx\n", dwStartType);

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hServiceKey,
                               L"ErrorControl",
                               NULL,
                               NULL,
                               (LPBYTE)&dwErrorControl,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    DPRINT("Error control: %lx\n", dwErrorControl);

    dwError = RegQueryValueExW(hServiceKey,
                               L"Tag",
                               NULL,
                               NULL,
                               (LPBYTE)&dwTagId,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
        dwTagId = 0;

    DPRINT("Tag: %lx\n", dwTagId);

    dwError = ScmReadString(hServiceKey,
                            L"Group",
                            &lpGroup);
    if (dwError != ERROR_SUCCESS)
        lpGroup = NULL;

    DPRINT("Group: %S\n", lpGroup);

    dwError = ScmReadString(hServiceKey,
                            L"DisplayName",
                            &lpDisplayName);
    if (dwError != ERROR_SUCCESS)
        lpDisplayName = NULL;

    DPRINT("Display name: %S\n", lpDisplayName);

    dwError = ScmCreateNewServiceRecord(lpServiceName,
                                        &lpService,
                                        dwServiceType,
                                        dwStartType);
    if (dwError != ERROR_SUCCESS)
        goto done;

    lpService->dwErrorControl = dwErrorControl;
    lpService->dwTag = dwTagId;

    if (lpGroup != NULL)
    {
        dwError = ScmSetServiceGroup(lpService, lpGroup);
        if (dwError != ERROR_SUCCESS)
            goto done;
    }

    if (lpDisplayName != NULL)
    {
        lpService->lpDisplayName = lpDisplayName;
        lpDisplayName = NULL;
    }

    DPRINT("ServiceName: '%S'\n", lpService->lpServiceName);
    if (lpService->lpGroup != NULL)
    {
        DPRINT("Group: '%S'\n", lpService->lpGroup->lpGroupName);
    }
    DPRINT("Start %lx  Type %lx  Tag %lx  ErrorControl %lx\n",
           lpService->dwStartType,
           lpService->Status.dwServiceType,
           lpService->dwTag,
           lpService->dwErrorControl);

    if (ScmIsDeleteFlagSet(hServiceKey))
        lpService->bDeleted = TRUE;
    else
        ScmGenerateServiceTag(lpService);

    if (lpService->Status.dwServiceType & SERVICE_WIN32)
    {
        dwError = ScmReadSecurityDescriptor(hServiceKey,
                                            &lpService->pSecurityDescriptor);
        if (dwError != ERROR_SUCCESS)
            goto done;

        /* Assing the default security descriptor if the security descriptor cannot be read */
        if (lpService->pSecurityDescriptor == NULL)
        {
            DPRINT("No security descriptor found! Assign default security descriptor!\n");
            dwError = ScmCreateDefaultServiceSD(&lpService->pSecurityDescriptor);
            if (dwError != ERROR_SUCCESS)
                goto done;

            dwError = ScmWriteSecurityDescriptor(hServiceKey,
                                                 lpService->pSecurityDescriptor);
            if (dwError != ERROR_SUCCESS)
                goto done;
        }
    }

done:
    if (lpGroup != NULL)
        HeapFree(GetProcessHeap(), 0, lpGroup);

    if (lpDisplayName != NULL)
        HeapFree(GetProcessHeap(), 0, lpDisplayName);

    if (lpService != NULL)
    {
        ASSERT(lpService->lpImage == NULL);
    }

    return dwError;
}
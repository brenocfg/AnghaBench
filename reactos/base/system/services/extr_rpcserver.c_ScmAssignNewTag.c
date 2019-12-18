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
typedef  int /*<<< orphan*/  pdwGroupTags ;
struct TYPE_9__ {struct TYPE_9__* Flink; } ;
struct TYPE_8__ {scalar_t__ dwTag; int /*<<< orphan*/  lpServiceName; TYPE_1__* lpGroup; TYPE_3__ ServiceListEntry; } ;
struct TYPE_7__ {int /*<<< orphan*/  szGroupName; } ;
typedef  TYPE_2__* PSERVICE ;
typedef  TYPE_3__* PLIST_ENTRY ;
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* CONTAINING_RECORD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  SERVICE ; 
 int /*<<< orphan*/  ServiceListEntry ; 
 int TAG_ARRAY_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

DWORD
ScmAssignNewTag(PSERVICE lpService)
{
    HKEY hKey = NULL;
    DWORD dwError;
    DWORD dwGroupTagCount = 0;
    PDWORD pdwGroupTags = NULL;
    DWORD dwFreeTag = 0;
    DWORD dwTagUsedBase = 1;
    BOOLEAN TagUsed[TAG_ARRAY_SIZE];
    INT nTagOffset;
    DWORD i;
    DWORD cbDataSize;
    PLIST_ENTRY ServiceEntry;
    PSERVICE CurrentService;

    ASSERT(lpService != NULL);
    ASSERT(lpService->lpGroup != NULL);

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"System\\CurrentControlSet\\Control\\GroupOrderList",
                            0,
                            KEY_READ,
                            &hKey);

    if (dwError != ERROR_SUCCESS)
        goto findFreeTag;

    /* query value length */
    cbDataSize = 0;
    dwError = RegQueryValueExW(hKey,
                               lpService->lpGroup->szGroupName,
                               NULL,
                               NULL,
                               NULL,
                               &cbDataSize);

    if (dwError != ERROR_SUCCESS && dwError != ERROR_MORE_DATA)
        goto findFreeTag;

    pdwGroupTags = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbDataSize);
    if (!pdwGroupTags)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        goto cleanup;
    }

    dwError = RegQueryValueExW(hKey,
                               lpService->lpGroup->szGroupName,
                               NULL,
                               NULL,
                               (LPBYTE)pdwGroupTags,
                               &cbDataSize);

    if (dwError != ERROR_SUCCESS)
        goto findFreeTag;

    if (cbDataSize < sizeof(pdwGroupTags[0]))
        goto findFreeTag;

    dwGroupTagCount = min(pdwGroupTags[0], cbDataSize / sizeof(pdwGroupTags[0]) - 1);

findFreeTag:
    do
    {
        /* mark all tags as unused */
        for (i = 0; i < TAG_ARRAY_SIZE; i++)
            TagUsed[i] = FALSE;

        /* mark tags in GroupOrderList as used */
        for (i = 1; i <= dwGroupTagCount; i++)
        {
            nTagOffset = pdwGroupTags[i] - dwTagUsedBase;
            if (nTagOffset >= 0 && nTagOffset < TAG_ARRAY_SIZE)
                TagUsed[nTagOffset] = TRUE;
        }

        /* mark tags in service list as used */
        ServiceEntry = lpService->ServiceListEntry.Flink;
        while (ServiceEntry != &lpService->ServiceListEntry)
        {
            ASSERT(ServiceEntry != NULL);
            CurrentService = CONTAINING_RECORD(ServiceEntry, SERVICE, ServiceListEntry);
            if (CurrentService->lpGroup == lpService->lpGroup)
            {
                nTagOffset = CurrentService->dwTag - dwTagUsedBase;
                if (nTagOffset >= 0 && nTagOffset < TAG_ARRAY_SIZE)
                    TagUsed[nTagOffset] = TRUE;
            }

            ServiceEntry = ServiceEntry->Flink;
        }

        /* find unused tag, if any */
        for (i = 0; i < TAG_ARRAY_SIZE; i++)
        {
            if (!TagUsed[i])
            {
                dwFreeTag = dwTagUsedBase + i;
                break;
            }
        }

        dwTagUsedBase += TAG_ARRAY_SIZE;
    } while (!dwFreeTag);

cleanup:
    if (pdwGroupTags)
        HeapFree(GetProcessHeap(), 0, pdwGroupTags);

    if (hKey)
        RegCloseKey(hKey);

    if (dwFreeTag)
    {
        lpService->dwTag = dwFreeTag;
        DPRINT("Assigning new tag %lu to service %S in group %S\n",
               lpService->dwTag, lpService->lpServiceName, lpService->lpGroup->szGroupName);
        dwError = ERROR_SUCCESS;
    }
    else
    {
        DPRINT1("Failed to assign new tag to service %S, error=%lu\n",
                lpService->lpServiceName, dwError);
    }

    return dwError;
}
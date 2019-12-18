#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szValue ;
typedef  int /*<<< orphan*/  szName ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int BootType; int /*<<< orphan*/  szOptions; int /*<<< orphan*/  szBootPath; int /*<<< orphan*/  szSectionName; } ;
typedef  TYPE_1__* PBOOTRECORD ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOTRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _wcsnicmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PBOOTRECORD
ReadFreeldrSection(HINF hInf, WCHAR *szSectionName)
{
    PBOOTRECORD pRecord;
    INFCONTEXT InfContext;
    WCHAR szName[MAX_PATH];
    WCHAR szValue[MAX_PATH];
    DWORD LineLength;

    if (!SetupFindFirstLineW(hInf,
                            szSectionName,
                            NULL,
                            &InfContext))
    {
        /* Failed to find section */
        return NULL;
    }

    pRecord = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BOOTRECORD));
    if (pRecord == NULL)
    {
        return NULL;
    }

    wcscpy(pRecord->szSectionName, szSectionName);

    do
    {
        if (!SetupGetStringFieldW(&InfContext,
                                  0,
                                  szName,
                                  sizeof(szName) / sizeof(WCHAR),
                                  &LineLength))
        {
            break;
        }

        if (!SetupGetStringFieldW(&InfContext,
                                  1,
                                  szValue,
                                  sizeof(szValue) / sizeof(WCHAR),
                                  &LineLength))
        {
            break;
        }

        if (!_wcsnicmp(szName, L"BootType", 8))
        {
            if (!_wcsnicmp(szValue, L"ReactOS", 7))
            {
                // FIXME: Store as enum
                pRecord->BootType = 1;
            }
            else
            {
                pRecord->BootType = 0;
            }
        }
        else if (!_wcsnicmp(szName, L"SystemPath", 10))
        {
            wcscpy(pRecord->szBootPath, szValue);
        }
        else if (!_wcsnicmp(szName, L"Options", 7))
        {
            // FIXME: Store flags as values
            wcscpy(pRecord->szOptions, szValue);
        }

    }
    while (SetupFindNextLine(&InfContext, &InfContext));

    return pRecord;
}
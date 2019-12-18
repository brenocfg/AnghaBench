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
typedef  int /*<<< orphan*/  szValue ;
typedef  int /*<<< orphan*/  szNumberA ;
typedef  int /*<<< orphan*/  szNumber ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int dwFlags; scalar_t__ (* procA ) (char*) ;scalar_t__ (* procW ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ ENUMSYSTEMCODEPAGES_CALLBACKS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
#define  CP_INSTALLED 129 
#define  CP_SUPPORTED 128 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 int MAX_PATH ; 
 scalar_t__ NLS_RegEnumValue (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ NLS_RegOpenKey (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (char*) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL NLS_EnumSystemCodePages(ENUMSYSTEMCODEPAGES_CALLBACKS *lpProcs)
{
    WCHAR szNumber[5 + 1], szValue[MAX_PATH];
    HANDLE hKey;
    BOOL bContinue = TRUE;
    ULONG ulIndex = 0;

    if (!lpProcs)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    switch (lpProcs->dwFlags)
    {
        case CP_INSTALLED:
        case CP_SUPPORTED:
            break;
        default:
            SetLastError(ERROR_INVALID_FLAGS);
            return FALSE;
    }

    hKey = NLS_RegOpenKey(0, L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\Control\\NLS\\CodePage");
    if (!hKey)
    {
        WARN("NLS_RegOpenKey() failed\n");
        return FALSE;
    }

    while (bContinue)
    {
        if (NLS_RegEnumValue(hKey, ulIndex, szNumber, sizeof(szNumber),
                             szValue, sizeof(szValue)))
        {
            if ((lpProcs->dwFlags == CP_SUPPORTED)||
                ((lpProcs->dwFlags == CP_INSTALLED)&&(wcslen(szValue) > 2)))
            {
                if (lpProcs->procW)
                {
                    bContinue = lpProcs->procW(szNumber);
                }
                else
                {
                    char szNumberA[sizeof(szNumber)/sizeof(WCHAR)];

                    WideCharToMultiByte(CP_ACP, 0, szNumber, -1, szNumberA, sizeof(szNumberA), 0, 0);
                    bContinue = lpProcs->procA(szNumberA);
                }
            }

            ulIndex++;

        } else bContinue = FALSE;

        if (!bContinue)
            break;
    }

    if (hKey)
        NtClose(hKey);

    return TRUE;
}
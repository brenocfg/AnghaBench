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
struct TYPE_3__ {int /*<<< orphan*/  hSelf; int /*<<< orphan*/ * szPagingFiles; } ;
typedef  TYPE_1__* PVIRTMEM ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowLastWin32Error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  lpKey ; 

__attribute__((used)) static BOOL
ReadPageFileSettings(PVIRTMEM pVirtMem)
{
    HKEY hkey = NULL;
    DWORD dwType;
    DWORD dwDataSize;
    BOOL bRet = FALSE;

    if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                       lpKey,
                       0,
                       NULL,
                       REG_OPTION_NON_VOLATILE,
                       KEY_QUERY_VALUE,
                       NULL,
                       &hkey,
                       NULL) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hkey,
                            _T("PagingFiles"),
                            NULL,
                            &dwType,
                            NULL,
                            &dwDataSize) == ERROR_SUCCESS)
        {
            pVirtMem->szPagingFiles = (LPTSTR)HeapAlloc(GetProcessHeap(),
                                                        0,
                                                        dwDataSize);
            if (pVirtMem->szPagingFiles != NULL)
            {
                ZeroMemory(pVirtMem->szPagingFiles,
                           dwDataSize);
                if (RegQueryValueEx(hkey,
                                    _T("PagingFiles"),
                                    NULL,
                                    &dwType,
                                    (PBYTE)pVirtMem->szPagingFiles,
                                    &dwDataSize) == ERROR_SUCCESS)
                {
                    bRet = TRUE;
                }
            }
        }
    }

    if (!bRet)
        ShowLastWin32Error(pVirtMem->hSelf);

    if (hkey != NULL)
        RegCloseKey(hkey);

    return bRet;
}
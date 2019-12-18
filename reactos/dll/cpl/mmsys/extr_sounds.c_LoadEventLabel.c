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
typedef  int /*<<< orphan*/  szDesc ;
typedef  int /*<<< orphan*/  szData ;
struct TYPE_6__ {TYPE_1__* pLabelMap; } ;
struct TYPE_5__ {struct TYPE_5__* Next; void* szIcon; void* szDesc; void* szName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PLABEL_MAP ;
typedef  TYPE_2__* PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LABEL_MAP ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _T (char*) ; 
 void* _tcsdup (int /*<<< orphan*/ *) ; 

BOOL
LoadEventLabel(PGLOBAL_DATA pGlobalData, HKEY hKey, TCHAR * szSubKey)
{
    HKEY hSubKey;
    DWORD cbValue;
    TCHAR szDesc[MAX_PATH];
    TCHAR szData[MAX_PATH];
    PLABEL_MAP pMap;

    if (RegOpenKeyEx(hKey,
                     szSubKey,
                     0,
                     KEY_READ,
                     &hSubKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    cbValue = sizeof(szDesc);
    if (RegQueryValueEx(hSubKey,
                      NULL,
                      NULL,
                      NULL,
                      (LPBYTE)szDesc,
                      &cbValue) != ERROR_SUCCESS)
    {
        RegCloseKey(hSubKey);
        return FALSE;
    }

    cbValue = sizeof(szData);
    if (RegQueryValueEx(hSubKey,
                        _T("DispFileName"),
                        NULL,
                        NULL,
                        (LPBYTE)szData,
                        &cbValue) != ERROR_SUCCESS)
    {
        RegCloseKey(hSubKey);
        return FALSE;
    }

    pMap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LABEL_MAP));
    if (!pMap)
    {
        return FALSE;
    }

    pMap->szName = _tcsdup(szSubKey);
    pMap->szDesc = _tcsdup(szDesc);
    pMap->szIcon = _tcsdup(szData);

    if (pGlobalData->pLabelMap)
    {
        pMap->Next = pGlobalData->pLabelMap;
        pGlobalData->pLabelMap = pMap;
    }
    else
    {
        pGlobalData->pLabelMap = pMap;
        pGlobalData->pLabelMap->Next = NULL;
    }
    return TRUE;
}
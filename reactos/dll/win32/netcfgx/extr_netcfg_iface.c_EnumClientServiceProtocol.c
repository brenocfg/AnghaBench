#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szText ;
typedef  int /*<<< orphan*/  szName ;
typedef  char WCHAR ;
struct TYPE_5__ {struct TYPE_5__* pNext; void* szBindName; void* szHelpText; void* szDisplayName; void* szId; scalar_t__ dwCharacteristics; int /*<<< orphan*/  InstanceId; int /*<<< orphan*/  ClassGUID; } ;
typedef  TYPE_1__ NetCfgComponentItem ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 void* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int REG_DWORD ; 
 int REG_SZ ; 
 int /*<<< orphan*/  ReadBindingString (TYPE_1__*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wcscpy (void*,char*) ; 
 int wcslen (char*) ; 

HRESULT
EnumClientServiceProtocol(HKEY hKey, const GUID * pGuid, NetCfgComponentItem ** pHead)
{
    DWORD dwIndex = 0;
    DWORD dwSize;
    DWORD dwType;
    WCHAR szName[100];
    WCHAR szText[100];
    HKEY hSubKey, hNDIKey;
    NetCfgComponentItem * pLast = NULL, *pCurrent;

    *pHead = NULL;
    do
    {
        szText[0] = L'\0';

        dwSize = sizeof(szName)/sizeof(WCHAR);
        if (RegEnumKeyExW(hKey, dwIndex++, szName, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            pCurrent = CoTaskMemAlloc(sizeof(NetCfgComponentItem));
            if (!pCurrent)
                return E_OUTOFMEMORY;

            ZeroMemory(pCurrent, sizeof(NetCfgComponentItem));
            CopyMemory(&pCurrent->ClassGUID, pGuid, sizeof(GUID));

            if (FAILED(CLSIDFromString(szName, &pCurrent->InstanceId)))
            {
                /// ReactOS tcpip guid is not yet generated
                //CoTaskMemFree(pCurrent);
                //return E_FAIL;
            }
            if (RegOpenKeyExW(hKey, szName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
            {
                /* retrieve Characteristics */
                dwSize = sizeof(DWORD);

                RegQueryValueExW(hSubKey, L"Characteristics", NULL, &dwType, (LPBYTE)&pCurrent->dwCharacteristics, &dwSize);
                if (dwType != REG_DWORD)
                    pCurrent->dwCharacteristics = 0;

                /* retrieve ComponentId */
                dwSize = sizeof(szText);
                if (RegQueryValueExW(hSubKey, L"ComponentId", NULL, &dwType, (LPBYTE)szText, &dwSize) == ERROR_SUCCESS)
                {
                    if (dwType == REG_SZ)
                    {
                        szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
                        pCurrent->szId = CoTaskMemAlloc((wcslen(szText)+1)* sizeof(WCHAR));
                        if (pCurrent->szId)
                            wcscpy(pCurrent->szId, szText);
                    }
                }

                /* retrieve Description */
                dwSize = sizeof(szText);
                if (RegQueryValueExW(hSubKey, L"Description", NULL, &dwType, (LPBYTE)szText, &dwSize) == ERROR_SUCCESS)
                {
                    if (dwType == REG_SZ)
                    {
                        szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
                        pCurrent->szDisplayName = CoTaskMemAlloc((wcslen(szText)+1)* sizeof(WCHAR));
                        if (pCurrent->szDisplayName)
                            wcscpy(pCurrent->szDisplayName, szText);
                    }
                }

                if (RegOpenKeyExW(hSubKey, L"NDI", 0, KEY_READ, &hNDIKey) == ERROR_SUCCESS)
                {
                    /* retrieve HelpText */
                    dwSize = sizeof(szText);
                    if (RegQueryValueExW(hNDIKey, L"HelpText", NULL, &dwType, (LPBYTE)szText, &dwSize) == ERROR_SUCCESS)
                    {
                        if (dwType == REG_SZ)
                        {
                            szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
                            pCurrent->szHelpText = CoTaskMemAlloc((wcslen(szText)+1)* sizeof(WCHAR));
                            if (pCurrent->szHelpText)
                                wcscpy(pCurrent->szHelpText, szText);
                        }
                    }

                    /* retrieve Service */
                    dwSize = sizeof(szText);
                    if (RegQueryValueExW(hNDIKey, L"Service", NULL, &dwType, (LPBYTE)szText, &dwSize) == ERROR_SUCCESS)
                    {
                        if (dwType == REG_SZ)
                        {
                            szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
                            pCurrent->szBindName = CoTaskMemAlloc((wcslen(szText)+1)* sizeof(WCHAR));
                            if (pCurrent->szBindName)
                                wcscpy(pCurrent->szBindName, szText);
                        }
                    }
                    RegCloseKey(hNDIKey);
                }
                RegCloseKey(hSubKey);

                ReadBindingString(pCurrent);

                if (!pLast)
                    *pHead = pCurrent;
                else
                    pLast->pNext = pCurrent;

                pLast = pCurrent;
            }
        }
        else
           break;

    }while(TRUE);
    return S_OK;
}
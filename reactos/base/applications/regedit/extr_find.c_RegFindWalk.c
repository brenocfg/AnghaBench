#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/ ***************** LPWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CompareName (int /*<<< orphan*/ *****************,int /*<<< orphan*/ ) ; 
 scalar_t__ DoEvents () ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ HKEY_CLASSES_ROOT ; 
 scalar_t__ HKEY_CURRENT_CONFIG ; 
 scalar_t__ HKEY_CURRENT_USER ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 scalar_t__ HKEY_USERS ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 int RSF_LOOKATKEYS ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegEnumKeyExW (scalar_t__,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegFindRecurse (scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ******************,int /*<<< orphan*/ ******************) ; 
 scalar_t__ RegOpenKeyExW (scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegQueryInfoKeyW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ ******************,int) ; 
 int /*<<< orphan*/ ************************* _wcsdup (int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *****************,scalar_t__*) ; 
 int /*<<< orphan*/  compare ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******************) ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__*,int /*<<< orphan*/ *****************,int) ; 
 int /*<<< orphan*/ ************************* malloc (int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ******************,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ***************** s_backslash ; 
 int s_cbName ; 
 int s_dwFlags ; 
 int /*<<< orphan*/ ***************** s_empty ; 
 int /*<<< orphan*/  s_szFindWhat ; 
 int /*<<< orphan*/  s_szName ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *****************,int /*<<< orphan*/ *****************) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,scalar_t__*) ; 
 int wcslen (scalar_t__*) ; 
 int /*<<< orphan*/ ************************* wcsrchr (scalar_t__*,int) ; 

BOOL RegFindWalk(
    HKEY *  phKey,
    LPCWSTR pszSubKey,
    LPCWSTR pszValueName,
    LPWSTR *ppszFoundSubKey,
    LPWSTR *ppszFoundValueName)
{
    LONG lResult;
    DWORD i, c;
    HKEY hBaseKey, hSubKey;
    WCHAR szKeyName[MAX_PATH];
    WCHAR szSubKey[MAX_PATH];
    LPWSTR pch;
    BOOL fPast;
    LPWSTR *ppszNames = NULL;

    hBaseKey = *phKey;
    if (RegFindRecurse(hBaseKey, pszSubKey, pszValueName, ppszFoundSubKey,
                       ppszFoundValueName))
        return TRUE;

    if (wcslen(pszSubKey) >= MAX_PATH)
        return FALSE;

    wcscpy(szSubKey, pszSubKey);
    while(szSubKey[0] != 0)
    {
        if (DoEvents())
            return FALSE;

        pch = wcsrchr(szSubKey, L'\\');
        if (pch == NULL)
        {
            wcscpy(szKeyName, szSubKey);
            szSubKey[0] = 0;
            hSubKey = hBaseKey;
        }
        else
        {
            lstrcpynW(szKeyName, pch + 1, MAX_PATH);
            *pch = 0;
            lResult = RegOpenKeyExW(hBaseKey, szSubKey, 0, KEY_ALL_ACCESS,
                                   &hSubKey);
            if (lResult != ERROR_SUCCESS)
                return FALSE;
        }

        lResult = RegQueryInfoKeyW(hSubKey, NULL, NULL, NULL, &c, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);
        if (lResult != ERROR_SUCCESS)
            goto err;

        ppszNames = (LPWSTR *) malloc(c * sizeof(LPWSTR));
        if (ppszNames == NULL)
            goto err;
        ZeroMemory(ppszNames, c * sizeof(LPWSTR));

        for(i = 0; i < c; i++)
        {
            if (DoEvents())
                goto err;

            s_cbName = MAX_PATH * sizeof(WCHAR);
            lResult = RegEnumKeyExW(hSubKey, i, s_szName, &s_cbName,
                                    NULL, NULL, NULL, NULL);
            if (lResult == ERROR_NO_MORE_ITEMS)
            {
                c = i;
                break;
            }
            if (lResult != ERROR_SUCCESS)
                break;
            ppszNames[i] = _wcsdup(s_szName);
        }

        qsort(ppszNames, c, sizeof(LPWSTR), compare);

        fPast = FALSE;
        for(i = 0; i < c; i++)
        {
            if (DoEvents())
                goto err;

            if (!fPast && _wcsicmp(ppszNames[i], szKeyName) == 0)
            {
                fPast = TRUE;
                continue;
            }
            if (!fPast)
                continue;

            if ((s_dwFlags & RSF_LOOKATKEYS) &&
                    CompareName(ppszNames[i], s_szFindWhat))
            {
                *ppszFoundSubKey = malloc(
                                       (wcslen(szSubKey) + wcslen(ppszNames[i]) + 2) *
                                       sizeof(WCHAR));
                if (*ppszFoundSubKey == NULL)
                    goto err;
                if (szSubKey[0])
                {
                    wcscpy(*ppszFoundSubKey, szSubKey);
                    wcscat(*ppszFoundSubKey, s_backslash);
                }
                else
                    **ppszFoundSubKey = 0;
                wcscat(*ppszFoundSubKey, ppszNames[i]);
                *ppszFoundValueName = NULL;
                goto success;
            }

            if (RegFindRecurse(hSubKey, ppszNames[i], NULL,
                               ppszFoundSubKey, ppszFoundValueName))
            {
                LPWSTR psz = *ppszFoundSubKey;
                *ppszFoundSubKey = malloc(
                                       (wcslen(szSubKey) + wcslen(psz) + 2) *
                                       sizeof(WCHAR));
                if (*ppszFoundSubKey == NULL)
                    goto err;
                if (szSubKey[0])
                {
                    wcscpy(*ppszFoundSubKey, szSubKey);
                    wcscat(*ppszFoundSubKey, s_backslash);
                }
                else
                    **ppszFoundSubKey = 0;
                wcscat(*ppszFoundSubKey, psz);
                free(psz);
                goto success;
            }
        }
        if (ppszNames != NULL)
        {
            for(i = 0; i < c; i++)
                free(ppszNames[i]);
            free(ppszNames);
        }
        ppszNames = NULL;

        if (hBaseKey != hSubKey)
            RegCloseKey(hSubKey);
    }

    if (*phKey == HKEY_CLASSES_ROOT)
    {
        *phKey = HKEY_CURRENT_USER;
        if (RegFindRecurse(*phKey, s_empty, NULL, ppszFoundSubKey,
                           ppszFoundValueName))
            return TRUE;
    }

    if (*phKey == HKEY_CURRENT_USER)
    {
        *phKey = HKEY_LOCAL_MACHINE;
        if (RegFindRecurse(*phKey, s_empty, NULL, ppszFoundSubKey,
                           ppszFoundValueName))
            goto success;
    }

    if (*phKey == HKEY_LOCAL_MACHINE)
    {
        *phKey = HKEY_USERS;
        if (RegFindRecurse(*phKey, s_empty, NULL, ppszFoundSubKey,
                           ppszFoundValueName))
            goto success;
    }

    if (*phKey == HKEY_USERS)
    {
        *phKey = HKEY_CURRENT_CONFIG;
        if (RegFindRecurse(*phKey, s_empty, NULL, ppszFoundSubKey,
                           ppszFoundValueName))
            goto success;
    }

err:
    if (ppszNames != NULL)
    {
        for(i = 0; i < c; i++)
            free(ppszNames[i]);
        free(ppszNames);
    }
    if (hBaseKey != hSubKey)
        RegCloseKey(hSubKey);
    return FALSE;

success:
    if (ppszNames != NULL)
    {
        for(i = 0; i < c; i++)
            free(ppszNames[i]);
        free(ppszNames);
    }
    if (hBaseKey != hSubKey)
        RegCloseKey(hSubKey);
    return TRUE;
}
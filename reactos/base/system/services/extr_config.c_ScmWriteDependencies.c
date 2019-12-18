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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int SIZE_T ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,char*) ; 
 int RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SC_GROUP_IDENTIFIERW ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,scalar_t__*) ; 
 int wcslen (scalar_t__*) ; 

DWORD
ScmWriteDependencies(HKEY hServiceKey,
                     LPCWSTR lpDependencies,
                     DWORD dwDependenciesLength)
{
    DWORD dwError = ERROR_SUCCESS;
    SIZE_T cchGroupLength = 0;
    SIZE_T cchServiceLength = 0;
    SIZE_T cchLength;
    LPWSTR lpGroupDeps;
    LPWSTR lpServiceDeps;
    LPCWSTR lpSrc;
    LPWSTR lpDst;

    if (*lpDependencies == 0)
    {
        RegDeleteValueW(hServiceKey,
                       L"DependOnService");
        RegDeleteValueW(hServiceKey,
                       L"DependOnGroup");
    }
    else
    {
        lpGroupDeps = HeapAlloc(GetProcessHeap(),
                                HEAP_ZERO_MEMORY,
                                (dwDependenciesLength + 2) * sizeof(WCHAR));
        if (lpGroupDeps == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;

        lpSrc = lpDependencies;
        lpDst = lpGroupDeps;
        while (*lpSrc != 0)
        {
            cchLength = wcslen(lpSrc) + 1;
            if (*lpSrc == SC_GROUP_IDENTIFIERW)
            {
                lpSrc++;
                cchLength--;
                cchGroupLength += cchLength;
                wcscpy(lpDst, lpSrc);
                lpDst = lpDst + cchLength;
            }

            lpSrc = lpSrc + cchLength;
        }
        *lpDst = 0;
        lpDst++;
        cchGroupLength++;

        lpSrc = lpDependencies;
        lpServiceDeps = lpDst;
        while (*lpSrc != 0)
        {
            cchLength = wcslen(lpSrc) + 1;
            if (*lpSrc != SC_GROUP_IDENTIFIERW)
            {
                cchServiceLength += cchLength;
                wcscpy(lpDst, lpSrc);
                lpDst = lpDst + cchLength;
            }

            lpSrc = lpSrc + cchLength;
        }
        *lpDst = 0;
        cchServiceLength++;

        if (cchGroupLength > 1)
        {
            dwError = RegSetValueExW(hServiceKey,
                                     L"DependOnGroup",
                                     0,
                                     REG_MULTI_SZ,
                                     (LPBYTE)lpGroupDeps,
                                     (DWORD)(cchGroupLength * sizeof(WCHAR)));
        }
        else
        {
            RegDeleteValueW(hServiceKey,
                            L"DependOnGroup");
        }

        if (dwError == ERROR_SUCCESS)
        {
            if (cchServiceLength > 1)
            {
                dwError = RegSetValueExW(hServiceKey,
                                         L"DependOnService",
                                         0,
                                         REG_MULTI_SZ,
                                         (LPBYTE)lpServiceDeps,
                                         (DWORD)(cchServiceLength * sizeof(WCHAR)));
            }
            else
            {
                RegDeleteValueW(hServiceKey,
                                L"DependOnService");
            }
        }

        HeapFree(GetProcessHeap(), 0, lpGroupDeps);
    }

    return dwError;
}
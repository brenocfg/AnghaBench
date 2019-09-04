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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * _alloca (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL
QueryGeneric(HKEY hKey, LPCTSTR pszValueNameT, DWORD dwExpectedType,
             LPVOID pvResult, DWORD dwResultSize)
{
    DWORD dwType, cbData;
    LPVOID *pTemp = _alloca(dwResultSize);

    ZeroMemory(pTemp, dwResultSize);

    cbData = dwResultSize;
    if (RegQueryValueEx(hKey, pszValueNameT, NULL, &dwType, (LPBYTE) pTemp, &cbData) != ERROR_SUCCESS)
        return FALSE;

    if (dwType != dwExpectedType)
        return FALSE;

    memcpy(pvResult, pTemp, cbData);
    return TRUE;
}
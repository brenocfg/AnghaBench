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
typedef  int /*<<< orphan*/  dwResult ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  QueryGeneric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL QueryByte(HKEY hKey, LPCTSTR pszValueName, BYTE *pbResult)
{
    DWORD dwResult;
    if (!QueryGeneric(hKey, pszValueName, REG_DWORD, &dwResult, sizeof(dwResult)))
        return FALSE;
    if (dwResult >= 0x100)
        return FALSE;
    *pbResult = (BYTE) dwResult;
    return TRUE;
}
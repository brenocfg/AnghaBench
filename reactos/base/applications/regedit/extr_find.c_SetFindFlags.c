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
typedef  int /*<<< orphan*/  dwData ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 int /*<<< orphan*/  s_szFindFlags ; 
 int /*<<< orphan*/  s_szFindFlagsR ; 

__attribute__((used)) static void SetFindFlags(DWORD dwFlags)
{
    HKEY hKey;
    DWORD dwDisposition;
    DWORD dwData;

    if (RegCreateKeyExW(HKEY_CURRENT_USER, g_szGeneralRegKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS)
    {
        dwData = (dwFlags >> 0) & 0x0000FFFF;
        RegSetValueExW(hKey, s_szFindFlags, 0, REG_DWORD, (const BYTE *) &dwData, sizeof(dwData));

        dwData = (dwFlags >> 16) & 0x0000FFFF;
        RegSetValueExW(hKey, s_szFindFlagsR, 0, REG_DWORD, (const BYTE *) &dwData, sizeof(dwData));

        RegCloseKey(hKey);
    }
}
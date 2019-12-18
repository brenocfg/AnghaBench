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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  REFGUID ;
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 scalar_t__ REG_CREATED_NEW_KEY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szwEnable ; 
 int /*<<< orphan*/  szwFullLangfmt ; 
 int /*<<< orphan*/  szwLngp ; 
 char* szwSystemTIPKey ; 

__attribute__((used)) static void add_userkey( REFCLSID rclsid, LANGID langid,
                                REFGUID guidProfile)
{
    HKEY key;
    WCHAR buf[39];
    WCHAR buf2[39];
    WCHAR fullkey[168];
    DWORD disposition = 0;
    ULONG res;

    TRACE("\n");

    StringFromGUID2(rclsid, buf, 39);
    StringFromGUID2(guidProfile, buf2, 39);
    swprintf(fullkey,szwFullLangfmt,szwSystemTIPKey,buf,szwLngp,langid,buf2);

    res = RegCreateKeyExW(HKEY_CURRENT_USER,fullkey, 0, NULL, 0,
                   KEY_READ | KEY_WRITE, NULL, &key, &disposition);

    if (!res && disposition == REG_CREATED_NEW_KEY)
    {
        DWORD zero = 0x0;
        RegSetValueExW(key, szwEnable, 0, REG_DWORD, (LPBYTE)&zero, sizeof(DWORD));
    }

    if (!res)
        RegCloseKey(key);
}
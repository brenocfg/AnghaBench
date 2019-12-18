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
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * PWINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  MSACM_RegisterDriver (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,...) ; 
 scalar_t__ _wcsnicmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

PWINE_ACMDRIVERID MSACM_RegisterDriverFromRegistry(LPCWSTR pszRegEntry)
{
    static const WCHAR msacmW[] = {'M','S','A','C','M','.'};
    static const WCHAR drvkey[] = {'S','o','f','t','w','a','r','e','\\',
				   'M','i','c','r','o','s','o','f','t','\\',
				   'W','i','n','d','o','w','s',' ','N','T','\\',
				   'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
				   'D','r','i','v','e','r','s','3','2','\0'};
    WCHAR buf[2048];
    DWORD bufLen, lRet;
    HKEY hKey;
    PWINE_ACMDRIVERID padid = NULL;
    
    /* The requested registry entry must have the format msacm.XXXXX in order to
       be recognized in any future sessions of msacm
     */
    if (0 == _wcsnicmp(pszRegEntry, msacmW, ARRAY_SIZE(msacmW))) {
        lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE, drvkey, 0, KEY_QUERY_VALUE, &hKey);
        if (lRet != ERROR_SUCCESS) {
            WARN("unable to open registry key - 0x%08x\n", lRet);
        } else {
            bufLen = sizeof(buf);
            lRet = RegQueryValueExW(hKey, pszRegEntry, NULL, NULL, (LPBYTE)buf, &bufLen);
            if (lRet != ERROR_SUCCESS) {
                WARN("unable to query requested subkey %s - 0x%08x\n", debugstr_w(pszRegEntry), lRet);
            } else {
                MSACM_RegisterDriver(pszRegEntry, buf, 0);
            }
            RegCloseKey( hKey );
        }
    }
    return padid;
}
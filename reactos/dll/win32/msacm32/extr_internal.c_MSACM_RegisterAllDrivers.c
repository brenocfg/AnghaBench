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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetPrivateProfileSectionW (char const*,char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  MSACM_RegisterDriver (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSACM_ReorderDriversByPriority () ; 
 scalar_t__ MSACM_pFirstACMDriverID ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsnicmp (char*,char const*,scalar_t__) ; 
 scalar_t__ lstrlenW (char*) ; 
 char* wcschr (char*,char) ; 

void MSACM_RegisterAllDrivers(void)
{
    static const WCHAR msacm32[] = {'m','s','a','c','m','3','2','.','d','l','l','\0'};
    static const WCHAR msacmW[] = {'M','S','A','C','M','.'};
    static const WCHAR drv32[] = {'d','r','i','v','e','r','s','3','2','\0'};
    static const WCHAR sys[] = {'s','y','s','t','e','m','.','i','n','i','\0'};
    static const WCHAR drvkey[] = {'S','o','f','t','w','a','r','e','\\',
				   'M','i','c','r','o','s','o','f','t','\\',
				   'W','i','n','d','o','w','s',' ','N','T','\\',
				   'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
				   'D','r','i','v','e','r','s','3','2','\0'};
    DWORD i, cnt, bufLen, lRet, type;
    WCHAR buf[2048], valname[64], *name, *s;
    FILETIME lastWrite;
    HKEY hKey;

    /* FIXME: What if the user edits system.ini while the program is running?
     * Does Windows handle that?  */
    if (MSACM_pFirstACMDriverID) return;

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE, drvkey, 0, KEY_QUERY_VALUE, &hKey);
    if (lRet == ERROR_SUCCESS) {
	RegQueryInfoKeyW( hKey, 0, 0, 0, &cnt, 0, 0, 0, 0, 0, 0, 0);
	for (i = 0; i < cnt; i++) {
	    bufLen = ARRAY_SIZE(buf);
	    lRet = RegEnumKeyExW(hKey, i, buf, &bufLen, 0, 0, 0, &lastWrite);
	    if (lRet != ERROR_SUCCESS) continue;
	    if (_wcsnicmp(buf, msacmW, ARRAY_SIZE(msacmW))) continue;
	    if (!(name = wcschr(buf, '='))) continue;
	    *name = 0;
	    MSACM_RegisterDriver(buf, name + 1, 0);
	}
	i = 0;
	cnt = ARRAY_SIZE(valname);
	bufLen = sizeof(buf);
	while(RegEnumValueW(hKey, i, valname, &cnt, 0,
		    &type, (BYTE*)buf, &bufLen) == ERROR_SUCCESS){
	    if (!_wcsnicmp(valname, msacmW, ARRAY_SIZE(msacmW)))
		MSACM_RegisterDriver(valname, buf, 0);
	    ++i;
	}
    	RegCloseKey( hKey );
    }

    if (GetPrivateProfileSectionW(drv32, buf, ARRAY_SIZE(buf), sys))
    {
	for(s = buf; *s;  s += lstrlenW(s) + 1)
	{
	    if (_wcsnicmp(s, msacmW, ARRAY_SIZE(msacmW))) continue;
	    if (!(name = wcschr(s, '='))) continue;
	    *name = 0;
	    MSACM_RegisterDriver(s, name + 1, 0);
	    *name = '=';
	}
    }
    MSACM_ReorderDriversByPriority();
    MSACM_RegisterDriver(msacm32, msacm32, 0);
}
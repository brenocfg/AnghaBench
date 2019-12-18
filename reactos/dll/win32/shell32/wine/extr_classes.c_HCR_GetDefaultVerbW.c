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
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegEnumKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int /*<<< orphan*/ ) ; 
 char* swCommand ; 
 char* swOpen ; 
 int /*<<< orphan*/  swShell ; 

BOOL HCR_GetDefaultVerbW( HKEY hkeyClass, LPCWSTR szVerb, LPWSTR szDest, DWORD len )
{
        WCHAR sTemp[MAX_PATH];
        LONG size;
        HKEY hkey;

	TRACE("%p %s %p\n", hkeyClass, debugstr_w(szVerb), szDest);

        if (szVerb && *szVerb)
        {
            lstrcpynW(szDest, szVerb, len);
            return TRUE;
        }

        size=len;
        *szDest='\0';
        if (!RegQueryValueW(hkeyClass, swShell, szDest, &size) && *szDest)
        {
            /* The MSDN says to first try the default verb */
            lstrcpyW(sTemp, swShell);
            lstrcatW(sTemp, szDest);
            lstrcatW(sTemp, swCommand);
            if (!RegOpenKeyExW(hkeyClass, sTemp, 0, KEY_READ, &hkey))
            {
                RegCloseKey(hkey);
                TRACE("default verb=%s\n", debugstr_w(szDest));
                return TRUE;
            }
        }

        /* then fallback to 'open' */
        lstrcpyW(sTemp, swShell);
        lstrcatW(sTemp, swOpen);
        lstrcatW(sTemp, swCommand);
        if (!RegOpenKeyExW(hkeyClass, sTemp, 0, KEY_READ, &hkey))
        {
            RegCloseKey(hkey);
            lstrcpynW(szDest, swOpen, len);
            TRACE("default verb=open\n");
            return TRUE;
        }

        /* and then just use the first verb on Windows >= 2000 */
#ifdef __REACTOS__
        if (!RegOpenKeyExW(hkeyClass, L"shell", 0, KEY_READ, &hkey))
        {
            if (!RegEnumKeyW(hkey, 0, szDest, len) && *szDest)
            {
                TRACE("default verb=first verb=%s\n", debugstr_w(szDest));
                RegCloseKey(hkey);
                return TRUE;
            }
            RegCloseKey(hkey);
        }
#else
        if (!RegEnumKeyW(hkeyClass, 0, szDest, len) && *szDest)
        {
            TRACE("default verb=first verb=%s\n", debugstr_w(szDest));
            return TRUE;
        }
#endif

        TRACE("no default verb!\n");
	return FALSE;
}
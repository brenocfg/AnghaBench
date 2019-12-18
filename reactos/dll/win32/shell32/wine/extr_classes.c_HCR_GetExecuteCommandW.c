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
typedef  int /*<<< orphan*/  sTempVerb ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ HCR_GetDefaultVerbW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SHGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * swCommand ; 
 int /*<<< orphan*/  swShell ; 

BOOL HCR_GetExecuteCommandW( HKEY hkeyClass, LPCWSTR szClass, LPCWSTR szVerb, LPWSTR szDest, DWORD len )
{
	WCHAR sTempVerb[MAX_PATH];
	BOOL ret;

	TRACE("%p %s %s %p\n", hkeyClass, debugstr_w(szClass), debugstr_w(szVerb), szDest);

	if (szClass)
            RegOpenKeyExW(HKEY_CLASSES_ROOT, szClass, 0, KEY_READ, &hkeyClass);
        if (!hkeyClass)
            return FALSE;
        ret = FALSE;

        if (HCR_GetDefaultVerbW(hkeyClass, szVerb, sTempVerb, sizeof(sTempVerb)/sizeof(sTempVerb[0])))
        {
            WCHAR sTemp[MAX_PATH];
            lstrcpyW(sTemp, swShell);
            lstrcatW(sTemp, sTempVerb);
            lstrcatW(sTemp, swCommand);
            ret = (ERROR_SUCCESS == SHGetValueW(hkeyClass, sTemp, NULL, NULL, szDest, &len));
        }
        if (szClass)
            RegCloseKey(hkeyClass);

	TRACE("-- %s\n", debugstr_w(szDest) );
	return ret;
}
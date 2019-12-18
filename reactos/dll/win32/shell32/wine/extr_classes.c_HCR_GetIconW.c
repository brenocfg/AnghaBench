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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HCR_RegGetIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ ,int) ; 

BOOL HCR_GetIconW(LPCWSTR szClass, LPWSTR szDest, LPCWSTR szName, DWORD len, int* picon_idx)
{
        static const WCHAR swDefaultIcon[] = {'\\','D','e','f','a','u','l','t','I','c','o','n',0};
	HKEY	hkey;
	WCHAR	sTemp[MAX_PATH];
	BOOL	ret = FALSE;

	TRACE("%s\n",debugstr_w(szClass) );

	lstrcpynW(sTemp, szClass, MAX_PATH);
	lstrcatW(sTemp, swDefaultIcon);

	if (!RegOpenKeyExW(HKEY_CLASSES_ROOT, sTemp, 0, KEY_READ, &hkey))
	{
	  ret = HCR_RegGetIconW(hkey, szDest, szName, len, picon_idx);
	  RegCloseKey(hkey);
	}

        if(ret)
            TRACE("-- %s %i\n", debugstr_w(szDest), *picon_idx);
        else
            TRACE("-- not found\n");

	return ret;
}
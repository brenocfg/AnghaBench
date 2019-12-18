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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  MAX_EXTENSION_LENGTH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegLoadMUIStringW (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int /*<<< orphan*/ ) ; 

BOOL HCR_MapTypeToValueW(LPCWSTR szExtension, LPWSTR szFileType, LONG len, BOOL bPrependDot)
{	
	HKEY	hkey;
	WCHAR	szTemp[MAX_EXTENSION_LENGTH + 2];

	TRACE("%s %p\n", debugstr_w(szExtension), szFileType);

        /* added because we do not want to have double dots */
        if (szExtension[0] == '.')
          bPrependDot = FALSE;

	if (bPrependDot)
	  szTemp[0] = '.';

	lstrcpynW(szTemp + (bPrependDot?1:0), szExtension, MAX_EXTENSION_LENGTH);

	if (RegOpenKeyExW(HKEY_CLASSES_ROOT, szTemp, 0, KEY_READ, &hkey))
	{ 
	  return FALSE;
	}

#ifdef __REACTOS__
        if (!RegLoadMUIStringW(hkey, L"FriendlyTypeName", szFileType, len, NULL, 0, NULL))
        {
            RegCloseKey(hkey);
            return TRUE;
        }
#endif

	if (RegQueryValueW(hkey, NULL, szFileType, &len))
	{ 
	  RegCloseKey(hkey);
	  return FALSE;
	}

	RegCloseKey(hkey);

	TRACE("--UE;\n} %s\n", debugstr_w(szFileType));

	return TRUE;
}
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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* LPWSTR ;
typedef  char* LPOLESTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_AdminFolderShortcut ; 
 int /*<<< orphan*/  CLSID_ControlPanel ; 
 int /*<<< orphan*/  CLSID_MyComputer ; 
 int /*<<< orphan*/  CLSID_MyDocuments ; 
 int /*<<< orphan*/  CLSID_RecycleBin ; 
 int /*<<< orphan*/  CLSID_ShellDesktop ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ HCR_RegOpenClassIDKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDS_ADMINISTRATIVETOOLS ; 
 int /*<<< orphan*/  IDS_CONTROLPANEL ; 
 int /*<<< orphan*/  IDS_DESKTOP ; 
 int /*<<< orphan*/  IDS_MYCOMPUTER ; 
 int /*<<< orphan*/  IDS_PERSONAL ; 
 int /*<<< orphan*/  IDS_RECYCLEBIN_FOLDER_NAME ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  RRF_RT_REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegGetValueW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RegLoadMUIStringW (int /*<<< orphan*/ ,char const*,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StringFromCLSID (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  shell32_hInstance ; 
 int /*<<< orphan*/  swEmpty ; 
 int /*<<< orphan*/  swprintf (char*,char*,char*) ; 

BOOL HCR_GetClassNameW(REFIID riid, LPWSTR szDest, DWORD len)
{	
	HKEY	hkey;
	BOOL ret = FALSE;
	DWORD buflen = len;
#ifdef __REACTOS__
        WCHAR szName[100];
        LPOLESTR pStr;
#endif

 	szDest[0] = 0;

#ifdef __REACTOS__
        if (StringFromCLSID(riid, &pStr) == S_OK)
        {
            DWORD dwLen = buflen * sizeof(WCHAR);
            swprintf(szName, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\%s", pStr);
            if (!RegGetValueW(HKEY_CURRENT_USER, szName, NULL, RRF_RT_REG_SZ, NULL, (PVOID)szDest, &dwLen))
            {
                ret = TRUE;
            }
            CoTaskMemFree(pStr);
        }
        if (!ret && HCR_RegOpenClassIDKey(riid, &hkey))
#else
	if (HCR_RegOpenClassIDKey(riid, &hkey))
#endif
	{
          static const WCHAR wszLocalizedString[] = 
            { 'L','o','c','a','l','i','z','e','d','S','t','r','i','n','g', 0 };
          if (!RegLoadMUIStringW(hkey, wszLocalizedString, szDest, len, NULL, 0, NULL) ||
              !RegQueryValueExW(hkey, swEmpty, 0, NULL, (LPBYTE)szDest, &len))
          {
	    ret = TRUE;
	  }
	  RegCloseKey(hkey);
	}

	if (!ret || !szDest[0])
	{
	  if(IsEqualIID(riid, &CLSID_ShellDesktop))
	  {
	    if (LoadStringW(shell32_hInstance, IDS_DESKTOP, szDest, buflen))
	      ret = TRUE;
	  }
	  else if (IsEqualIID(riid, &CLSID_MyComputer))
	  {
	    if(LoadStringW(shell32_hInstance, IDS_MYCOMPUTER, szDest, buflen))
	      ret = TRUE;
	  }
#ifdef __REACTOS__
          else if (IsEqualIID(riid, &CLSID_MyDocuments))
          {
              if(LoadStringW(shell32_hInstance, IDS_PERSONAL, szDest, buflen))
                  ret = TRUE;
          }
          else if (IsEqualIID(riid, &CLSID_RecycleBin))
          {
              if(LoadStringW(shell32_hInstance, IDS_RECYCLEBIN_FOLDER_NAME, szDest, buflen))
                  ret = TRUE;
          }
          else if (IsEqualIID(riid, &CLSID_ControlPanel))
          {
              if(LoadStringW(shell32_hInstance, IDS_CONTROLPANEL, szDest, buflen))
                  ret = TRUE;
          }
          else if (IsEqualIID(riid, &CLSID_AdminFolderShortcut))
          {
              if(LoadStringW(shell32_hInstance, IDS_ADMINISTRATIVETOOLS, szDest, buflen))
                  ret = TRUE;
          }
#endif
	}
	TRACE("-- %s\n", debugstr_w(szDest));
	return ret;
}
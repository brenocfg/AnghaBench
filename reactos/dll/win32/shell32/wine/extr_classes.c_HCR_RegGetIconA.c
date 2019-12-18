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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandEnvironmentStringsA (char*,char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 scalar_t__ ParseFieldA (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  PathUnquoteSpacesA (char*) ; 
 scalar_t__ REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,char*,scalar_t__) ; 

__attribute__((used)) static BOOL HCR_RegGetIconA(HKEY hkey, LPSTR szDest, LPCSTR szName, DWORD len, int* picon_idx)
{
	DWORD dwType;
	char sTemp[MAX_PATH];
	char  sNum[5];

	if (!RegQueryValueExA(hkey, szName, 0, &dwType, (LPBYTE)szDest, &len))
	{
          if (dwType == REG_EXPAND_SZ)
	  {
	    ExpandEnvironmentStringsA(szDest, sTemp, MAX_PATH);
	    lstrcpynA(szDest, sTemp, len);
	  }
	  if (ParseFieldA (szDest, 2, sNum, 5))
             *picon_idx=atoi(sNum);
          else
             *picon_idx=0; /* sometimes the icon number is missing */
	  ParseFieldA (szDest, 1, szDest, len);
          PathUnquoteSpacesA(szDest);
	  return TRUE;
	}
	return FALSE;
}
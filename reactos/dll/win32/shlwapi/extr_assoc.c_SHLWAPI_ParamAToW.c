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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL SHLWAPI_ParamAToW(LPCSTR lpszParam, LPWSTR lpszBuff, DWORD dwLen,
                              LPWSTR* lpszOut)
{
  if (lpszParam)
  {
    DWORD dwStrLen = MultiByteToWideChar(CP_ACP, 0, lpszParam, -1, NULL, 0);

    if (dwStrLen < dwLen)
    {
      *lpszOut = lpszBuff; /* Use Buffer, it is big enough */
    }
    else
    {
      /* Create a new buffer big enough for the string */
      *lpszOut = HeapAlloc(GetProcessHeap(), 0,
                                   dwStrLen * sizeof(WCHAR));
      if (!*lpszOut)
        return FALSE;
    }
    MultiByteToWideChar(CP_ACP, 0, lpszParam, -1, *lpszOut, dwStrLen);
  }
  else
    *lpszOut = NULL;
  return TRUE;
}
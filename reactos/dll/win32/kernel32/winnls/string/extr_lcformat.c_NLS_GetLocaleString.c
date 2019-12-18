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
typedef  int /*<<< orphan*/  LCID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlenW (char*) ; 

__attribute__((used)) static WCHAR* NLS_GetLocaleString(LCID lcid, DWORD dwFlags)
{
  WCHAR szBuff[80], *str;
  DWORD dwLen;

  szBuff[0] = '\0';
  GetLocaleInfoW(lcid, dwFlags, szBuff, ARRAY_SIZE(szBuff));
  dwLen = strlenW(szBuff) + 1;
  str = HeapAlloc(GetProcessHeap(), 0, dwLen * sizeof(WCHAR));
  if (str)
    memcpy(str, szBuff, dwLen * sizeof(WCHAR));
  return str;
}
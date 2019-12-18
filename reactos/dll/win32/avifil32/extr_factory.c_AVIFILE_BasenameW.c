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
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  SLASH (char) ; 
 int lstrlenW (char*) ; 

LPCWSTR AVIFILE_BasenameW(LPCWSTR szPath)
{
#define SLASH(w) ((w) == '/' || (w) == '\\')

  LPCWSTR szCur;

  for (szCur = szPath + lstrlenW(szPath);
       szCur > szPath && !SLASH(*szCur) && *szCur != ':';)
    szCur--;

  if (szCur == szPath)
    return szCur;
  else
    return szCur + 1;

#undef SLASH
}
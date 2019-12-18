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
typedef  int /*<<< orphan*/  NUMBERFMTW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int LONGLONG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FillNumberFmt (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int GetNumberFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 

__attribute__((used)) static int FormatInt(LONGLONG qdwValue, LPWSTR pszBuf, int cchBuf)
{
  NUMBERFMTW fmt;
  WCHAR decimal[8], thousand[8];
  WCHAR buf[24];
  WCHAR *c;
  BOOL neg = (qdwValue < 0);

  FillNumberFmt(&fmt, decimal, sizeof decimal / sizeof (WCHAR),
                thousand, sizeof thousand / sizeof (WCHAR));

  c = &buf[24];
  *(--c) = 0;
  do
  {
    *(--c) = '0' + (qdwValue%10);
    qdwValue /= 10;
  } while (qdwValue > 0);
  if (neg)
    *(--c) = '-';
  
  return GetNumberFormatW(LOCALE_USER_DEFAULT, 0, c, &fmt, pszBuf, cchBuf);
}
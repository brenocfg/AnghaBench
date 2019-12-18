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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 char HIBYTE (int /*<<< orphan*/ ) ; 
 scalar_t__ IsDBCSLeadByte (char) ; 
 char LOBYTE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL SHLWAPI_ChrCmpHelperA(WORD ch1, WORD ch2, DWORD dwFlags)
{
  char str1[3], str2[3];

  str1[0] = LOBYTE(ch1);
  if (IsDBCSLeadByte(str1[0]))
  {
    str1[1] = HIBYTE(ch1);
    str1[2] = '\0';
  }
  else
    str1[1] = '\0';

  str2[0] = LOBYTE(ch2);
  if (IsDBCSLeadByte(str2[0]))
  {
    str2[1] = HIBYTE(ch2);
    str2[2] = '\0';
  }
  else
    str2[1] = '\0';

  return CompareStringA(GetThreadLocale(), dwFlags, str1, -1, str2, -1) - CSTR_EQUAL;
}
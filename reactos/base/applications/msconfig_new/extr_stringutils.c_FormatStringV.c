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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  LPCTSTR ;

/* Variables and functions */
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  StringCchVPrintf (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _vsctprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LPTSTR FormatStringV(LPCTSTR str, va_list args)
{
    LPTSTR lpszString;
    size_t strLenPlusNull;

    if (!str) return NULL;

    strLenPlusNull = _vsctprintf(str, args) + 1;

    lpszString = (LPTSTR)MemAlloc(0, strLenPlusNull * sizeof(TCHAR));
    if (!lpszString) return NULL;

    StringCchVPrintf(lpszString, strLenPlusNull, str, args);

    return lpszString;
}
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
typedef  int* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  StringCchCopyNW (int*,size_t,int /*<<< orphan*/ ,size_t) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 

LPWSTR DuplicateStringWEx(LPCWSTR str, size_t numOfChars)
{
    LPWSTR dupStr;
    size_t strSize;

    if (!str) return NULL;

    strSize = min(wcslen(str), numOfChars);

    dupStr = (LPWSTR)MemAlloc(0, (strSize + 1) * sizeof(WCHAR));
    if (!dupStr) return NULL;

    StringCchCopyNW(dupStr, strSize + 1, str, strSize);
    dupStr[strSize] = L'\0';

    return dupStr;
}
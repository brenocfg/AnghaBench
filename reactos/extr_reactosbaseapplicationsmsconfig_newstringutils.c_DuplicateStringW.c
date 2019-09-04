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
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  StringCchCopyW (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

LPWSTR DuplicateStringW(LPCWSTR str)
{
    LPWSTR dupStr;
    size_t strSizePlusNull;

    if (!str) return NULL;

    strSizePlusNull = wcslen(str) + 1;

    dupStr = (LPWSTR)MemAlloc(0, strSizePlusNull * sizeof(WCHAR));
    if (!dupStr) return NULL;

    StringCchCopyW(dupStr, strSizePlusNull, str);

    return dupStr;
}
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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int RSF_MATCHCASE ; 
 int RSF_WHOLESTRING ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lstrstri (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s_dwFlags ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wcsstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CompareName(LPCWSTR pszName1, LPCWSTR pszName2)
{
    if (s_dwFlags & RSF_WHOLESTRING)
    {
        if (s_dwFlags & RSF_MATCHCASE)
            return wcscmp(pszName1, pszName2) == 0;
        else
            return _wcsicmp(pszName1, pszName2) == 0;
    }
    else
    {
        if (s_dwFlags & RSF_MATCHCASE)
            return wcsstr(pszName1, pszName2) != NULL;
        else
            return lstrstri(pszName1, pszName2) != NULL;
    }
}
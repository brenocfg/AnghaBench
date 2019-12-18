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
typedef  int /*<<< orphan*/  PUXINI_FILE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UXINI_GetNextValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL UXINI_FindValue(PUXINI_FILE uf, LPCWSTR lpName, LPCWSTR *lpValue, DWORD *dwValueLen)
{
    LPCWSTR name;
    DWORD namelen;

    while((name = UXINI_GetNextValue(uf, &namelen, lpValue, dwValueLen))) {
        if(CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, name, namelen, lpName, -1) == CSTR_EQUAL) {
            return TRUE;
        }
    }
    return FALSE;
}
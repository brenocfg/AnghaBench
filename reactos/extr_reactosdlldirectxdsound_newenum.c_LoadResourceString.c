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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LoadStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsound_hInstance ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
LoadResourceString(
    UINT ResourceId,
    LPVOID Buffer,
    UINT ccount,
    LPVOID DefaultString,
    BOOL bUnicode)
{
    if (bUnicode)
    {
        /* load localized string */
        if (!LoadStringW(dsound_hInstance, ResourceId, (LPWSTR)Buffer, ccount))
        {
            /* default device name */
            wcscpy((LPWSTR)Buffer, (LPWSTR)DefaultString);
        }
    }
    else
    {
        /* load localized string */
        if (!LoadStringA(dsound_hInstance, ResourceId, (LPSTR)Buffer, ccount))
        {
            /* default device name */
            strcpy((LPSTR)Buffer, (LPSTR)DefaultString);
        }
    }
}
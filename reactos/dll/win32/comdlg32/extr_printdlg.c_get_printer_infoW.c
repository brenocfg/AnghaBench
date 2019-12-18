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
typedef  int /*<<< orphan*/  PRINTER_INFO_2W ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetPrinterW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static PRINTER_INFO_2W * get_printer_infoW(HANDLE hprn)
{
    PRINTER_INFO_2W *pi2 = NULL;
    DWORD needed = 0;
    BOOL res;

    res = GetPrinterW(hprn, 2, NULL, 0, &needed);
    if (!res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
        pi2 = HeapAlloc(GetProcessHeap(), 0, needed);
        res = GetPrinterW(hprn, 2, (LPBYTE)pi2, needed, &needed);
    }

    if (res)
        return pi2;

    TRACE("GetPrinterW failed with %u\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, pi2);
    return NULL;
}
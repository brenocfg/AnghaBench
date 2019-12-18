#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dwPrivate; struct TYPE_5__* lpstrElementName; struct TYPE_5__* lpstrAlias; struct TYPE_5__* lpstrDeviceType; struct TYPE_5__* lpNext; int /*<<< orphan*/  hDriver; } ;
typedef  TYPE_1__* LPWINE_MCIDRIVER ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* MciDrivers ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINMM_cs ; 

__attribute__((used)) static	BOOL	MCI_UnLoadMciDriver(LPWINE_MCIDRIVER wmd)
{
    LPWINE_MCIDRIVER*		tmp;

    if (!wmd)
	return TRUE;

    CloseDriver(wmd->hDriver, 0, 0);

    if (wmd->dwPrivate != 0)
	WARN("Unloading mci driver with non nul dwPrivate field\n");

    EnterCriticalSection(&WINMM_cs);
    for (tmp = &MciDrivers; *tmp; tmp = &(*tmp)->lpNext) {
	if (*tmp == wmd) {
	    *tmp = wmd->lpNext;
	    break;
	}
    }
    LeaveCriticalSection(&WINMM_cs);

    HeapFree(GetProcessHeap(), 0, wmd->lpstrDeviceType);
    HeapFree(GetProcessHeap(), 0, wmd->lpstrAlias);
    HeapFree(GetProcessHeap(), 0, wmd->lpstrElementName);

    HeapFree(GetProcessHeap(), 0, wmd);
    return TRUE;
}
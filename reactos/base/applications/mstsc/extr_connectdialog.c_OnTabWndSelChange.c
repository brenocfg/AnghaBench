#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  hDisplayPage; int /*<<< orphan*/  hGeneralPage; int /*<<< orphan*/  hTab; } ;
typedef  TYPE_1__* PINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BringWindowToTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TabCtrl_GetCurSel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
OnTabWndSelChange(PINFO pInfo)
{
    switch (TabCtrl_GetCurSel(pInfo->hTab))
    {
        case 0: //General
            ShowWindow(pInfo->hGeneralPage, SW_SHOW);
            ShowWindow(pInfo->hDisplayPage, SW_HIDE);
            BringWindowToTop(pInfo->hGeneralPage);
            break;
        case 1: //Display
            ShowWindow(pInfo->hGeneralPage, SW_HIDE);
            ShowWindow(pInfo->hDisplayPage, SW_SHOW);
            BringWindowToTop(pInfo->hDisplayPage);
            break;
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ti ;
struct TYPE_6__ {int /*<<< orphan*/  hwndToolTip; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {int cbSize; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTM_TRACKACTIVATE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static inline void
TRACKBAR_ActivateToolTip (const TRACKBAR_INFO *infoPtr, BOOL fShow)
{
    TTTOOLINFOW ti;

    if (!infoPtr->hwndToolTip) return;

    ZeroMemory(&ti, sizeof(ti));
    ti.cbSize = sizeof(ti);
    ti.hwnd   = infoPtr->hwndSelf;

    SendMessageW (infoPtr->hwndToolTip, TTM_TRACKACTIVATE, fShow, (LPARAM)&ti);
}
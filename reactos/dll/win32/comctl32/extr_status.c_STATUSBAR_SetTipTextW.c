#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hwndToolTip; int /*<<< orphan*/  Self; } ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  lpszText; scalar_t__ hinst; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTM_UPDATETIPTEXTW ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
STATUSBAR_SetTipTextW (const STATUS_INFO *infoPtr, INT id, LPWSTR text)
{
    TRACE("part %d: \"%s\"\n", id, debugstr_w(text));
    if (infoPtr->hwndToolTip) {
	TTTOOLINFOW ti;
	ti.cbSize = sizeof(TTTOOLINFOW);
	ti.hwnd = infoPtr->Self;
	ti.uId = id;
	ti.hinst = 0;
	ti.lpszText = text;
	SendMessageW (infoPtr->hwndToolTip, TTM_UPDATETIPTEXTW, 0, (LPARAM)&ti);
    }

    return 0;
}
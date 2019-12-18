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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {int NtfUnicode; scalar_t__ hwndSelf; int /*<<< orphan*/  hwndNotify; } ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 scalar_t__ NF_REQUERY ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static LRESULT COMBOEX_NotifyFormat (COMBOEX_INFO *infoPtr, LPARAM lParam)
{
    if (lParam == NF_REQUERY) {
	INT i = SendMessageW(infoPtr->hwndNotify,
			 WM_NOTIFYFORMAT, (WPARAM)infoPtr->hwndSelf, NF_QUERY);
        infoPtr->NtfUnicode = (i == NFR_UNICODE);
    }
    return infoPtr->NtfUnicode ? NFR_UNICODE : NFR_ANSI;
}
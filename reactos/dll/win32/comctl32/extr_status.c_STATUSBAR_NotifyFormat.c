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
struct TYPE_3__ {int bUnicode; scalar_t__ Self; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 scalar_t__ NF_REQUERY ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static LRESULT
STATUSBAR_NotifyFormat (STATUS_INFO *infoPtr, HWND from, INT cmd)
{
    if (cmd == NF_REQUERY) {
	INT i = SendMessageW(from, WM_NOTIFYFORMAT, (WPARAM)infoPtr->Self, NF_QUERY);
	infoPtr->bUnicode = (i == NFR_UNICODE);
    }
    return infoPtr->bUnicode ? NFR_UNICODE : NFR_ANSI;
}
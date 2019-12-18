#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {short x; short y; } ;
struct TYPE_7__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_9__ {int dwHitInfo; TYPE_1__ hdr; scalar_t__ dwItemData; TYPE_6__ pt; int /*<<< orphan*/  dwItemSpec; } ;
struct TYPE_8__ {int /*<<< orphan*/  Self; int /*<<< orphan*/  Notify; } ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  TYPE_3__ NMMOUSE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUSBAR_InternalHitTest (TYPE_2__ const*,TYPE_6__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static LRESULT
STATUSBAR_SendMouseNotify(const STATUS_INFO *infoPtr, UINT code, UINT msg, WPARAM wParam, LPARAM lParam)
{
    NMMOUSE  nm;

    TRACE("code %04x, lParam=%lx\n", code, lParam);
    nm.hdr.hwndFrom = infoPtr->Self;
    nm.hdr.idFrom = GetWindowLongPtrW(infoPtr->Self, GWLP_ID);
    nm.hdr.code = code;
    nm.pt.x = (short)LOWORD(lParam);
    nm.pt.y = (short)HIWORD(lParam);
    nm.dwItemSpec = STATUSBAR_InternalHitTest(infoPtr, &nm.pt);
    nm.dwItemData = 0;
    nm.dwHitInfo = 0x30000;     /* seems constant */

    /* Do default processing if WM_NOTIFY returns zero */
    if(!SendMessageW(infoPtr->Notify, WM_NOTIFY, nm.hdr.idFrom, (LPARAM)&nm))
    {
      return DefWindowProcW(infoPtr->Self, msg, wParam, lParam);
    }
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_6__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_8__ {int wVKey; TYPE_1__ hdr; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ uFocus; scalar_t__ uNumItem; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_2__ TAB_INFO ;
typedef  TYPE_3__ NMTCKEYDOWN ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_SetCurFocus (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TCN_KEYDOWN ; 
#define  VK_LEFT 129 
#define  VK_RIGHT 128 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static LRESULT TAB_KeyDown(TAB_INFO* infoPtr, WPARAM keyCode, LPARAM lParam)
{
  INT newItem = -1;
  NMTCKEYDOWN nm;

  /* TCN_KEYDOWN notification sent always */
  nm.hdr.hwndFrom = infoPtr->hwnd;
  nm.hdr.idFrom = GetWindowLongPtrW(infoPtr->hwnd, GWLP_ID);
  nm.hdr.code = TCN_KEYDOWN;
  nm.wVKey = keyCode;
  nm.flags = lParam;
  SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, nm.hdr.idFrom, (LPARAM)&nm);

  switch (keyCode)
  {
    case VK_LEFT:
      newItem = infoPtr->uFocus - 1;
      break;
    case VK_RIGHT:
      newItem = infoPtr->uFocus + 1;
      break;
  }

  /* If we changed to a valid item, change focused item */
  if (newItem >= 0 && newItem < infoPtr->uNumItem && infoPtr->uFocus != newItem)
      TAB_SetCurFocus(infoPtr, newItem);

  return 0;
}
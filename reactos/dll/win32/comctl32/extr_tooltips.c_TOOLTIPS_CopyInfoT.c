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
struct TYPE_8__ {TYPE_1__* tools; } ;
struct TYPE_7__ {scalar_t__ cbSize; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  uFlags; } ;
struct TYPE_6__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  uFlags; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TTTOOLINFOW ;
typedef  TYPE_3__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ IS_INTRESOURCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  MAX_TEXT_SIZE_A ; 
 scalar_t__ TTTOOLINFOW_V2_SIZE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
TOOLTIPS_CopyInfoT (const TOOLTIPS_INFO *infoPtr, INT index, TTTOOLINFOW *ti, BOOL isW)
{
    const TTTOOL_INFO *toolPtr = &infoPtr->tools[index];

    ti->uFlags = toolPtr->uFlags;
    ti->hwnd   = toolPtr->hwnd;
    ti->uId    = toolPtr->uId;
    ti->rect   = toolPtr->rect;
    ti->hinst  = toolPtr->hinst;

    if (ti->lpszText) {
        if (toolPtr->lpszText == NULL ||
            IS_INTRESOURCE(toolPtr->lpszText) ||
            toolPtr->lpszText == LPSTR_TEXTCALLBACKW)
            ti->lpszText = toolPtr->lpszText;
        else if (isW)
            strcpyW (ti->lpszText, toolPtr->lpszText);
        else
            /* ANSI version, the buffer is maximum 80 bytes without null. */
            WideCharToMultiByte(CP_ACP, 0, toolPtr->lpszText, -1,
                                (LPSTR)ti->lpszText, MAX_TEXT_SIZE_A, NULL, NULL);
    }

    if (ti->cbSize >= TTTOOLINFOW_V2_SIZE)
        ti->lParam = toolPtr->lParam;

    /* lpReserved is intentionally not set. */
}
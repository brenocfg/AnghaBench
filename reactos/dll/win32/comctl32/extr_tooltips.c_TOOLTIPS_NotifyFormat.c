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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_5__ {scalar_t__ hwndSelf; TYPE_1__* tools; } ;
struct TYPE_4__ {scalar_t__ bNotifyUnicode; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ LPARAM ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 scalar_t__ NF_QUERY ; 
 scalar_t__ NF_REQUERY ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static LRESULT
TOOLTIPS_NotifyFormat (TOOLTIPS_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
#ifdef __REACTOS__
    TTTOOL_INFO *toolPtr = infoPtr->tools;
    LRESULT nResult;

    TRACE("infoPtr=%p wParam=%lx lParam=%p\n", infoPtr, wParam, (PVOID)lParam);

    if (lParam == NF_QUERY) {
        if (toolPtr->bNotifyUnicode) {
            return NFR_UNICODE;
        } else {
            return NFR_ANSI;
        }
    }
    else if (lParam == NF_REQUERY) {
        nResult = SendMessageW (toolPtr->hwnd, WM_NOTIFYFORMAT,
                    (WPARAM)infoPtr->hwndSelf, (LPARAM)NF_QUERY);
        if (nResult == NFR_ANSI) {
            toolPtr->bNotifyUnicode = FALSE;
            TRACE(" -- WM_NOTIFYFORMAT returns: NFR_ANSI\n");
        } else if (nResult == NFR_UNICODE) {
            toolPtr->bNotifyUnicode = TRUE;
            TRACE(" -- WM_NOTIFYFORMAT returns: NFR_UNICODE\n");
        } else {
            TRACE (" -- WM_NOTIFYFORMAT returns: error!\n");
        }
        return nResult;
    }
#else
    FIXME ("hwnd=%p wParam=%lx lParam=%lx\n", infoPtr->hwndSelf, wParam, lParam);
#endif

    return 0;
}
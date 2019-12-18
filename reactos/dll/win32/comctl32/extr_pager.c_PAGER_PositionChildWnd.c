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
struct TYPE_6__ {int nPos; scalar_t__ TLbtnState; int dwStyle; int nWidth; int nHeight; scalar_t__ hwndChild; int /*<<< orphan*/  hwndSelf; scalar_t__ nButtonSize; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ PAGER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_TOP ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PGF_GRAYED ; 
 int PGS_HORZ ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
PAGER_PositionChildWnd(PAGER_INFO* infoPtr)
{
    if (infoPtr->hwndChild)
    {
        RECT rcClient;
        int nPos = infoPtr->nPos;

        /* compensate for a grayed btn, which will soon become invisible */
        if (infoPtr->TLbtnState == PGF_GRAYED)
            nPos += infoPtr->nButtonSize;

        GetClientRect(infoPtr->hwndSelf, &rcClient);

        if (infoPtr->dwStyle & PGS_HORZ)
        {
            int wndSize = max(0, rcClient.right - rcClient.left);
            if (infoPtr->nWidth < wndSize)
                infoPtr->nWidth = wndSize;

            TRACE("[%p] SWP %dx%d at (%d,%d)\n", infoPtr->hwndSelf,
                         infoPtr->nWidth, infoPtr->nHeight,
                         -nPos, 0);
            SetWindowPos(infoPtr->hwndChild, HWND_TOP,
                         -nPos, 0,
                         infoPtr->nWidth, infoPtr->nHeight, 0);
        }
        else
        {
            int wndSize = max(0, rcClient.bottom - rcClient.top);
            if (infoPtr->nHeight < wndSize)
                infoPtr->nHeight = wndSize;

            TRACE("[%p] SWP %dx%d at (%d,%d)\n", infoPtr->hwndSelf,
                         infoPtr->nWidth, infoPtr->nHeight,
                         0, -nPos);
            SetWindowPos(infoPtr->hwndChild, HWND_TOP,
                         0, -nPos,
                         infoPtr->nWidth, infoPtr->nHeight, 0);
        }

        InvalidateRect(infoPtr->hwndChild, NULL, TRUE);
    }
}
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
typedef  scalar_t__ WORD ;
struct TYPE_6__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bRectsValid; scalar_t__ nHeight; scalar_t__ hFont; } ;
struct TYPE_5__ {scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HFONT ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ VERT_BORDER ; 

__attribute__((used)) static LRESULT
HEADER_SetFont (HEADER_INFO *infoPtr, HFONT hFont, WORD Redraw)
{
    TEXTMETRICW tm;
    HFONT hOldFont;
    HDC hdc;

    infoPtr->hFont = hFont;

    hdc = GetDC (0);
    hOldFont = SelectObject (hdc, infoPtr->hFont ? infoPtr->hFont : GetStockObject (SYSTEM_FONT));
    GetTextMetricsW (hdc, &tm);
    infoPtr->nHeight = tm.tmHeight + VERT_BORDER;
    SelectObject (hdc, hOldFont);
    ReleaseDC (0, hdc);

    infoPtr->bRectsValid = FALSE;

    if (Redraw) {
        InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);
    }

    return 0;
}
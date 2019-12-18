#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_18__ {void* bottom; } ;
struct TYPE_17__ {void* left; } ;
struct TYPE_16__ {void* left; } ;
struct TYPE_22__ {int nrFields; int* fieldspec; scalar_t__ select; int dwStyle; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hMonthCal; void* bDropdownEnabled; TYPE_4__ date; TYPE_3__ rcClient; TYPE_2__ rcDraw; TYPE_1__ calbutton; void* bCalDepressed; } ;
struct TYPE_21__ {void* y; void* x; } ;
struct TYPE_20__ {scalar_t__ top; scalar_t__ bottom; void* left; void* right; } ;
typedef  TYPE_4__ SYSTEMTIME ;
typedef  TYPE_5__ RECT ;
typedef  TYPE_6__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  void* INT ;
typedef  TYPE_7__ DATETIME_INFO ;

/* Variables and functions */
 int DATETIME_GetPrevDateField (TYPE_7__*,int) ; 
 int DATETIME_HitTest (TYPE_7__*,TYPE_6__) ; 
 int /*<<< orphan*/  DATETIME_SendSimpleNotify (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATETIME_SetSelectedField (TYPE_7__*,int) ; 
 scalar_t__ DTHT_MCPOPUP ; 
 int DTHT_NODATEMASK ; 
 int DTHT_NONE ; 
 int /*<<< orphan*/  DTN_CLOSEUP ; 
 int /*<<< orphan*/  DTN_DROPDOWN ; 
 int DTS_RIGHTALIGN ; 
 int DT_STRING ; 
 void* FALSE ; 
 int FULLDAY ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCM_GETMINREQRECT ; 
 int /*<<< orphan*/  MCM_SETCURSEL ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_5__*,void*,void*) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* TRUE ; 

__attribute__((used)) static LRESULT
DATETIME_LButtonDown (DATETIME_INFO *infoPtr, INT x, INT y)
{
    POINT pt;
    int new;

    pt.x = x;
    pt.y = y;
    new = DATETIME_HitTest (infoPtr, pt);

    SetFocus(infoPtr->hwndSelf);

    if (!(new & DTHT_NODATEMASK) || (new == DTHT_NONE))
    {
        if (new == DTHT_NONE)
            new = infoPtr->nrFields - 1;
        else
        {
            /* hitting string part moves selection to next date field to left */
            if (infoPtr->fieldspec[new] & DT_STRING)
            {
                new = DATETIME_GetPrevDateField(infoPtr, new);
                if (new == -1) return 0;
            }
            /* never select full day of week */
            if (infoPtr->fieldspec[new] == FULLDAY) return 0;
        }
    }

    DATETIME_SetSelectedField(infoPtr, new);

    if (infoPtr->select == DTHT_MCPOPUP) {
        RECT rcMonthCal;
        POINT pos;
        SendMessageW(infoPtr->hMonthCal, MCM_GETMINREQRECT, 0, (LPARAM)&rcMonthCal);

        /* FIXME: button actually is only depressed during dropdown of the */
        /* calendar control and when the mouse is over the button window */
        infoPtr->bCalDepressed = TRUE;

        /* recalculate the position of the monthcal popup */
        if(infoPtr->dwStyle & DTS_RIGHTALIGN)
            pos.x = infoPtr->calbutton.left - (rcMonthCal.right - rcMonthCal.left);
        else
            /* FIXME: this should be after the area reserved for the checkbox */
            pos.x = infoPtr->rcDraw.left;

        pos.y = infoPtr->rcClient.bottom;
        OffsetRect( &rcMonthCal, pos.x, pos.y );
        MapWindowPoints( infoPtr->hwndSelf, 0, (POINT *)&rcMonthCal, 2 );
        SetWindowPos(infoPtr->hMonthCal, 0, rcMonthCal.left, rcMonthCal.top,
                     rcMonthCal.right - rcMonthCal.left, rcMonthCal.bottom - rcMonthCal.top, 0);

        if(IsWindowVisible(infoPtr->hMonthCal)) {
            ShowWindow(infoPtr->hMonthCal, SW_HIDE);
            infoPtr->bDropdownEnabled = FALSE;
            DATETIME_SendSimpleNotify (infoPtr, DTN_CLOSEUP);
        } else {
            const SYSTEMTIME *lprgSysTimeArray = &infoPtr->date;
            TRACE("update calendar %04d/%02d/%02d\n", 
            lprgSysTimeArray->wYear, lprgSysTimeArray->wMonth, lprgSysTimeArray->wDay);
            SendMessageW(infoPtr->hMonthCal, MCM_SETCURSEL, 0, (LPARAM)(&infoPtr->date));

            if (infoPtr->bDropdownEnabled) {
                ShowWindow(infoPtr->hMonthCal, SW_SHOW);
                DATETIME_SendSimpleNotify (infoPtr, DTN_DROPDOWN);
            }
            infoPtr->bDropdownEnabled = TRUE;
        }

        TRACE ("dt:%p mc:%p mc parent:%p, desktop:%p\n",
               infoPtr->hwndSelf, infoPtr->hMonthCal, infoPtr->hwndNotify, GetDesktopWindow ());
    }

    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  wDayOfWeek; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_12__ {scalar_t__ hUpdown; int /*<<< orphan*/  pendingUpdown; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hwndCheckbut; TYPE_1__ date; int /*<<< orphan*/  hMonthCal; int /*<<< orphan*/  dateValid; } ;
struct TYPE_11__ {scalar_t__ code; scalar_t__ hwndFrom; } ;
struct TYPE_10__ {int /*<<< orphan*/  iDelta; } ;
typedef  TYPE_2__ NM_UPDOWN ;
typedef  TYPE_3__ NMHDR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_4__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETCHECK ; 
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  DATETIME_SendDateTimeChangeNotify (TYPE_4__*) ; 
 int /*<<< orphan*/  DATETIME_SendSimpleNotify (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTN_CLOSEUP ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCM_GETCURSEL ; 
 scalar_t__ MCN_SELECT ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UDN_DELTAPOS ; 

__attribute__((used)) static LRESULT
DATETIME_Notify (DATETIME_INFO *infoPtr, const NMHDR *lpnmh)
{
    TRACE ("Got notification %x from %p\n", lpnmh->code, lpnmh->hwndFrom);
    TRACE ("info: %p %p %p\n", infoPtr->hwndSelf, infoPtr->hMonthCal, infoPtr->hUpdown);

    if (lpnmh->code == MCN_SELECT) {
        ShowWindow(infoPtr->hMonthCal, SW_HIDE);
        infoPtr->dateValid = TRUE;
        SendMessageW (infoPtr->hMonthCal, MCM_GETCURSEL, 0, (LPARAM)&infoPtr->date);
        TRACE("got from calendar %04d/%02d/%02d day of week %d\n", 
        infoPtr->date.wYear, infoPtr->date.wMonth, infoPtr->date.wDay, infoPtr->date.wDayOfWeek);
        SendMessageW (infoPtr->hwndCheckbut, BM_SETCHECK, BST_CHECKED, 0);
        InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
        DATETIME_SendDateTimeChangeNotify (infoPtr);
        DATETIME_SendSimpleNotify(infoPtr, DTN_CLOSEUP);
    }
    if ((lpnmh->hwndFrom == infoPtr->hUpdown) && (lpnmh->code == UDN_DELTAPOS)) {
        const NM_UPDOWN *lpnmud = (const NM_UPDOWN*)lpnmh;
        TRACE("Delta pos %d\n", lpnmud->iDelta);
        infoPtr->pendingUpdown = lpnmud->iDelta;
    }
    return 0;
}
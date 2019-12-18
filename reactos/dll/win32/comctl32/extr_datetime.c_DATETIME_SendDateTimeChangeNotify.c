#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  date; scalar_t__ dateValid; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_6__ {TYPE_1__ nmhdr; int /*<<< orphan*/  st; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_2__ NMDATETIMECHANGE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ DATETIME_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DTN_DATETIMECHANGE ; 
 int /*<<< orphan*/  GDT_NONE ; 
 int /*<<< orphan*/  GDT_VALID ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static BOOL
DATETIME_SendDateTimeChangeNotify (const DATETIME_INFO *infoPtr)
{
    NMDATETIMECHANGE dtdtc;

    dtdtc.nmhdr.hwndFrom = infoPtr->hwndSelf;
    dtdtc.nmhdr.idFrom   = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
    dtdtc.nmhdr.code     = DTN_DATETIMECHANGE;

    dtdtc.dwFlags = infoPtr->dateValid ? GDT_VALID : GDT_NONE;

    dtdtc.st = infoPtr->date;
    return (BOOL) SendMessageW (infoPtr->hwndNotify, WM_NOTIFY,
                                dtdtc.nmhdr.idFrom, (LPARAM)&dtdtc);
}
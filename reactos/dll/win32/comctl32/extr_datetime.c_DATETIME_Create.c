#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  style; } ;
struct TYPE_9__ {int nrFieldsAllocated; int select; int /*<<< orphan*/  hFont; void* dateValid; int /*<<< orphan*/  date; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hMonthCal; void* bDropdownEnabled; int /*<<< orphan*/  hwndNotify; void* buflen; void* fieldRect; void* fieldspec; int /*<<< orphan*/  dwStyle; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STYLESTRUCT ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_2__ DATETIME_INFO ;
typedef  TYPE_3__ CREATESTRUCTW ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATETIME_SetFormatW (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATETIME_StyleChanged (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetLocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_CLASSW ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int WS_BORDER ; 
 int WS_CLIPSIBLINGS ; 
 int WS_POPUP ; 

__attribute__((used)) static LRESULT
DATETIME_Create (HWND hwnd, const CREATESTRUCTW *lpcs)
{
    DATETIME_INFO *infoPtr = Alloc (sizeof(DATETIME_INFO));
    STYLESTRUCT ss = { 0, lpcs->style };

    if (!infoPtr) return -1;

    infoPtr->hwndSelf = hwnd;
    infoPtr->dwStyle = lpcs->style;

    infoPtr->nrFieldsAllocated = 32;
    infoPtr->fieldspec = Alloc (infoPtr->nrFieldsAllocated * sizeof(int));
    infoPtr->fieldRect = Alloc (infoPtr->nrFieldsAllocated * sizeof(RECT));
    infoPtr->buflen = Alloc (infoPtr->nrFieldsAllocated * sizeof(int));
    infoPtr->hwndNotify = lpcs->hwndParent;
    infoPtr->select = -1; /* initially, nothing is selected */
    infoPtr->bDropdownEnabled = TRUE;

    DATETIME_StyleChanged(infoPtr, GWL_STYLE, &ss);
    DATETIME_SetFormatW (infoPtr, 0);

    /* create the monthcal control */
    infoPtr->hMonthCal = CreateWindowExW (0, MONTHCAL_CLASSW, 0, WS_BORDER | WS_POPUP | WS_CLIPSIBLINGS,
					  0, 0, 0, 0, infoPtr->hwndSelf, 0, 0, 0);

    /* initialize info structure */
    GetLocalTime (&infoPtr->date);
    infoPtr->dateValid = TRUE;
    infoPtr->hFont = GetStockObject(DEFAULT_GUI_FONT);

    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_9__ {int /*<<< orphan*/  style; int /*<<< orphan*/  hwndParent; } ;
struct TYPE_8__ {int iHotItem; int iHotDivider; int iMargin; int filter_change_timeout; scalar_t__ nHeight; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  nNotifyFormat; scalar_t__ himl; scalar_t__ iMoveItem; int /*<<< orphan*/  dwStyle; void* bTracking; void* bPressed; void* hcurDivopen; void* hcurDivider; void* hcurArrow; void* bRectsValid; scalar_t__ order; scalar_t__ items; scalar_t__ hFont; scalar_t__ uNumItem; scalar_t__ hwndSelf; } ;
struct TYPE_7__ {scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_3__ CREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTL32_hModule ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IDC_ARROW ; 
 int /*<<< orphan*/  IDC_DIVIDER ; 
 int /*<<< orphan*/  IDC_DIVIDEROPEN ; 
 void* LoadCursorW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_QUERY ; 
 int /*<<< orphan*/  OpenThemeData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VERT_BORDER ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  themeClass ; 

__attribute__((used)) static LRESULT
HEADER_Create (HWND hwnd, const CREATESTRUCTW *lpcs)
{
    HEADER_INFO *infoPtr;
    TEXTMETRICW tm;
    HFONT hOldFont;
    HDC   hdc;

    infoPtr = heap_alloc_zero (sizeof(*infoPtr));
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    infoPtr->hwndSelf = hwnd;
    infoPtr->hwndNotify = lpcs->hwndParent;
    infoPtr->uNumItem = 0;
    infoPtr->hFont = 0;
    infoPtr->items = 0;
    infoPtr->order = 0;
    infoPtr->bRectsValid = FALSE;
    infoPtr->hcurArrow = LoadCursorW (0, (LPWSTR)IDC_ARROW);
    infoPtr->hcurDivider = LoadCursorW (COMCTL32_hModule, MAKEINTRESOURCEW(IDC_DIVIDER));
    infoPtr->hcurDivopen = LoadCursorW (COMCTL32_hModule, MAKEINTRESOURCEW(IDC_DIVIDEROPEN));
    infoPtr->bPressed  = FALSE;
    infoPtr->bTracking = FALSE;
    infoPtr->dwStyle = lpcs->style;
    infoPtr->iMoveItem = 0;
    infoPtr->himl = 0;
    infoPtr->iHotItem = -1;
    infoPtr->iHotDivider = -1;
    infoPtr->iMargin = 3*GetSystemMetrics(SM_CXEDGE);
    infoPtr->nNotifyFormat =
	SendMessageW (infoPtr->hwndNotify, WM_NOTIFYFORMAT, (WPARAM)hwnd, NF_QUERY);
    infoPtr->filter_change_timeout = 1000;

    hdc = GetDC (0);
    hOldFont = SelectObject (hdc, GetStockObject (SYSTEM_FONT));
    GetTextMetricsW (hdc, &tm);
    infoPtr->nHeight = tm.tmHeight + VERT_BORDER;
    SelectObject (hdc, hOldFont);
    ReleaseDC (0, hdc);

    OpenThemeData(hwnd, themeClass);

    return 0;
}
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
struct TYPE_6__ {int style; int /*<<< orphan*/  hwndParent; } ;
struct TYPE_5__ {int dwStyle; int nButtonSize; int direction; int /*<<< orphan*/  hwndSelf; void* BRbtnState; void* TLbtnState; void* bCapture; void* bForward; scalar_t__ nHeight; scalar_t__ nWidth; scalar_t__ nPos; scalar_t__ nBorder; int /*<<< orphan*/  clrBk; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/ * hwndChild; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_2__ CREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 void* PGF_INVISIBLE ; 
 int PGS_DRAGNDROP ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_alloc_zero (int) ; 

__attribute__((used)) static LRESULT
PAGER_Create (HWND hwnd, const CREATESTRUCTW *lpcs)
{
    PAGER_INFO *infoPtr;

    /* allocate memory for info structure */
    infoPtr = heap_alloc_zero (sizeof(*infoPtr));
    if (!infoPtr) return -1;
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    /* set default settings */
    infoPtr->hwndSelf = hwnd;
    infoPtr->hwndChild = NULL;
    infoPtr->hwndNotify = lpcs->hwndParent;
    infoPtr->dwStyle = lpcs->style;
    infoPtr->clrBk = GetSysColor(COLOR_BTNFACE);
    infoPtr->nBorder = 0;
    infoPtr->nButtonSize = 12;
    infoPtr->nPos = 0;
    infoPtr->nWidth = 0;
    infoPtr->nHeight = 0;
    infoPtr->bForward = FALSE;
    infoPtr->bCapture = FALSE;
    infoPtr->TLbtnState = PGF_INVISIBLE;
    infoPtr->BRbtnState = PGF_INVISIBLE;
    infoPtr->direction = -1;

    if (infoPtr->dwStyle & PGS_DRAGNDROP)
        FIXME("[%p] Drag and Drop style is not implemented yet.\n", infoPtr->hwndSelf);

    return 0;
}
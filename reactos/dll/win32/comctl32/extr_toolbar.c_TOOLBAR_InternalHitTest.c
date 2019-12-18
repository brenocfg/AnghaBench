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
struct TYPE_5__ {int fsState; int fsStyle; int /*<<< orphan*/  rect; } ;
struct TYPE_4__ {int /*<<< orphan*/  nNumButtons; TYPE_2__* buttons; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BTNS_SEP ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int TBSTATE_HIDDEN ; 
 int /*<<< orphan*/  TOOLBAR_NOWHERE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static INT
TOOLBAR_InternalHitTest (const TOOLBAR_INFO *infoPtr, const POINT *lpPt, BOOL *button)
{
    TBUTTON_INFO *btnPtr;
    INT i;

    if (button)
        *button = FALSE;

    btnPtr = infoPtr->buttons;
    for (i = 0; i < infoPtr->nNumButtons; i++, btnPtr++) {
	if (btnPtr->fsState & TBSTATE_HIDDEN)
	    continue;

	if (btnPtr->fsStyle & BTNS_SEP) {
	    if (PtInRect (&btnPtr->rect, *lpPt)) {
		TRACE(" ON SEPARATOR %d\n", i);
		return -i;
	    }
	}
	else {
	    if (PtInRect (&btnPtr->rect, *lpPt)) {
		TRACE(" ON BUTTON %d\n", i);
                if (button)
                    *button = TRUE;
		return i;
	    }
	}
    }

    TRACE(" NOWHERE\n");
    return TOOLBAR_NOWHERE;
}
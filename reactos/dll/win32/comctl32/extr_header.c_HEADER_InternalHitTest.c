#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_16__ {scalar_t__ uNumItem; TYPE_1__* items; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_15__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_14__ {int right; int left; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_13__ {TYPE_2__ rect; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int INT ;
typedef  TYPE_4__ HEADER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DIVIDER_WIDTH ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ HEADER_IndexToOrder (TYPE_4__ const*,size_t) ; 
 scalar_t__ HEADER_IsItemFixed (TYPE_4__ const*,size_t) ; 
 size_t HEADER_PrevItem (TYPE_4__ const*,size_t) ; 
 size_t HHT_ABOVE ; 
 size_t HHT_BELOW ; 
 size_t HHT_NOWHERE ; 
 size_t HHT_ONDIVIDER ; 
 size_t HHT_ONDIVOPEN ; 
 size_t HHT_ONHEADER ; 
 size_t HHT_TOLEFT ; 
 size_t HHT_TORIGHT ; 
 scalar_t__ PtInRect (TYPE_2__*,TYPE_3__ const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void
HEADER_InternalHitTest (const HEADER_INFO *infoPtr, const POINT *lpPt, UINT *pFlags, INT *pItem)
{
    RECT rect, rcTest;
    UINT iCount;
    INT width;
    BOOL bNoWidth;

    GetClientRect (infoPtr->hwndSelf, &rect);

    *pFlags = 0;
    bNoWidth = FALSE;
    if (PtInRect (&rect, *lpPt))
    {
	if (infoPtr->uNumItem == 0) {
	    *pFlags |= HHT_NOWHERE;
	    *pItem = 1;
	    TRACE("NOWHERE\n");
	    return;
	}
	else {
	    /* somewhere inside */
	    for (iCount = 0; iCount < infoPtr->uNumItem; iCount++) {
		rect = infoPtr->items[iCount].rect;
		width = rect.right - rect.left;
		if (width == 0) {
		    bNoWidth = TRUE;
		    continue;
		}
		if (PtInRect (&rect, *lpPt)) {
		    if (width <= 2 * DIVIDER_WIDTH) {
			*pFlags |= HHT_ONHEADER;
			*pItem = iCount;
			TRACE("ON HEADER %d\n", iCount);
			return;
		    }
                    if (HEADER_IndexToOrder(infoPtr, iCount) > 0) {
			rcTest = rect;
			rcTest.right = rcTest.left + DIVIDER_WIDTH;
			if (PtInRect (&rcTest, *lpPt)) {
			    if (HEADER_IsItemFixed(infoPtr, HEADER_PrevItem(infoPtr, iCount)))
			    {
				*pFlags |= HHT_ONHEADER;
                                *pItem = iCount;
				TRACE("ON HEADER %d\n", *pItem);
				return;
			    }
			    if (bNoWidth) {
				*pFlags |= HHT_ONDIVOPEN;
                                *pItem = HEADER_PrevItem(infoPtr, iCount);
				TRACE("ON DIVOPEN %d\n", *pItem);
				return;
			    }
			    else {
				*pFlags |= HHT_ONDIVIDER;
                                *pItem = HEADER_PrevItem(infoPtr, iCount);
				TRACE("ON DIVIDER %d\n", *pItem);
				return;
			    }
			}
		    }
		    rcTest = rect;
		    rcTest.left = rcTest.right - DIVIDER_WIDTH;
		    if (!HEADER_IsItemFixed(infoPtr, iCount) && PtInRect (&rcTest, *lpPt))
		    {
			*pFlags |= HHT_ONDIVIDER;
			*pItem = iCount;
			TRACE("ON DIVIDER %d\n", *pItem);
			return;
		    }

		    *pFlags |= HHT_ONHEADER;
		    *pItem = iCount;
		    TRACE("ON HEADER %d\n", iCount);
		    return;
		}
	    }

	    /* check for last divider part (on nowhere) */
	    if (!HEADER_IsItemFixed(infoPtr, infoPtr->uNumItem - 1))
	    {
		rect = infoPtr->items[infoPtr->uNumItem-1].rect;
		rect.left = rect.right;
		rect.right += DIVIDER_WIDTH;
		if (PtInRect (&rect, *lpPt)) {
		    if (bNoWidth) {
			*pFlags |= HHT_ONDIVOPEN;
			*pItem = infoPtr->uNumItem - 1;
			TRACE("ON DIVOPEN %d\n", *pItem);
			return;
		    }
		    else {
			*pFlags |= HHT_ONDIVIDER;
			*pItem = infoPtr->uNumItem - 1;
			TRACE("ON DIVIDER %d\n", *pItem);
			return;
		    }
		}
	    }

	    *pFlags |= HHT_NOWHERE;
	    *pItem = 1;
	    TRACE("NOWHERE\n");
	    return;
	}
    }
    else {
	if (lpPt->x < rect.left) {
	   TRACE("TO LEFT\n");
	   *pFlags |= HHT_TOLEFT;
	}
	else if (lpPt->x > rect.right) {
	    TRACE("TO RIGHT\n");
	    *pFlags |= HHT_TORIGHT;
	}

	if (lpPt->y < rect.top) {
	    TRACE("ABOVE\n");
	    *pFlags |= HHT_ABOVE;
	}
	else if (lpPt->y > rect.bottom) {
	    TRACE("BELOW\n");
	    *pFlags |= HHT_BELOW;
	}
    }

    *pItem = 1;
    TRACE("flags=0x%X\n", *pFlags);
    return;
}
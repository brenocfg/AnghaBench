#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum SCROLL_HITTEST { ____Placeholder_SCROLL_HITTEST } SCROLL_HITTEST ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {scalar_t__ dxyLineButton; scalar_t__ xyThumbTop; scalar_t__ xyThumbBottom; TYPE_3__ rcScrollBar; } ;
typedef  TYPE_1__ SCROLLBARINFO ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PtInRect (TYPE_3__*,TYPE_2__) ; 
 int SCROLL_BOTTOM_ARROW ; 
 int SCROLL_BOTTOM_RECT ; 
 int SCROLL_NOWHERE ; 
 int /*<<< orphan*/  SCROLL_PtInRectEx (TYPE_3__*,TYPE_2__,scalar_t__) ; 
 int SCROLL_THUMB ; 
 int SCROLL_TOP_ARROW ; 
 int SCROLL_TOP_RECT ; 

__attribute__((used)) static enum SCROLL_HITTEST SCROLL_HitTest( HWND hwnd, SCROLLBARINFO* psbi, BOOL vertical,
                                           POINT pt, BOOL bDragging )
{
    if ( (bDragging && !SCROLL_PtInRectEx( &psbi->rcScrollBar, pt, vertical )) ||
	     (!PtInRect( &psbi->rcScrollBar, pt )) ) 
    {
         return SCROLL_NOWHERE;
    }

    if (vertical)
    {
        if (pt.y < psbi->rcScrollBar.top + psbi->dxyLineButton) 
            return SCROLL_TOP_ARROW;
        if (pt.y >= psbi->rcScrollBar.bottom - psbi->dxyLineButton) 
            return SCROLL_BOTTOM_ARROW;
        if (!psbi->xyThumbTop) 
            return SCROLL_TOP_RECT;
        pt.y -= psbi->rcScrollBar.top;
        if (pt.y < psbi->xyThumbTop) 
            return SCROLL_TOP_RECT;
        if (pt.y >= psbi->xyThumbBottom) 
            return SCROLL_BOTTOM_RECT;
    }
    else  /* horizontal */
    {
        if (pt.x < psbi->rcScrollBar.left + psbi->dxyLineButton)
            return SCROLL_TOP_ARROW;
        if (pt.x >= psbi->rcScrollBar.right - psbi->dxyLineButton) 
            return SCROLL_BOTTOM_ARROW;
        if (!psbi->xyThumbTop) 
            return SCROLL_TOP_RECT;
        pt.x -= psbi->rcScrollBar.left;
        if (pt.x < psbi->xyThumbTop) 
            return SCROLL_TOP_RECT;
        if (pt.x >= psbi->xyThumbBottom) 
            return SCROLL_BOTTOM_RECT;
    }
    return SCROLL_THUMB;
}
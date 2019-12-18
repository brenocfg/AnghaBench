#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* top; void* left; } ;
struct TYPE_12__ {void* top; void* left; } ;
struct TYPE_14__ {TYPE_2__ rcWindow; TYPE_1__ rcClient; } ;
struct TYPE_17__ {TYPE_3__ wi; } ;
struct TYPE_16__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_15__ {scalar_t__ dxyLineButton; scalar_t__ xyThumbBottom; scalar_t__ xyThumbTop; TYPE_5__ rcScrollBar; } ;
typedef  TYPE_4__ SCROLLBARINFO ;
typedef  TYPE_5__ RECT ;
typedef  TYPE_6__* PDRAW_CONTEXT ;
typedef  void* INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_NORMAL ; 
 int /*<<< orphan*/  SBP_GRIPPERHORZ ; 
 int /*<<< orphan*/  SBP_GRIPPERVERT ; 
 int /*<<< orphan*/  SBP_LOWERTRACKHORZ ; 
 int /*<<< orphan*/  SBP_LOWERTRACKVERT ; 
 int /*<<< orphan*/  SBP_THUMBBTNHORZ ; 
 int /*<<< orphan*/  SBP_THUMBBTNVERT ; 
 int /*<<< orphan*/  SBP_UPPERTRACKHORZ ; 
 int /*<<< orphan*/  SBP_UPPERTRACKVERT ; 
 int /*<<< orphan*/  SCROLL_BOTTOM_RECT ; 
 int /*<<< orphan*/  SCROLL_THUMB ; 
 int /*<<< orphan*/  SCROLL_TOP_RECT ; 
 int /*<<< orphan*/  SCROLL_ThemeDrawPart (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int,TYPE_5__*) ; 

__attribute__((used)) static void SCROLL_DrawInterior( PDRAW_CONTEXT pcontext, SCROLLBARINFO* psbi,
                                  INT thumbPos, BOOL vertical,
                                  int htDown, int htHot )
{
    RECT r, rcPart;

    /* thumbPos is relative to the edge of the scrollbar */

    r = psbi->rcScrollBar;
    if (vertical)
    {
        if (thumbPos)
            thumbPos += pcontext->wi.rcClient.top - pcontext->wi.rcWindow.top;
        r.top    += psbi->dxyLineButton;
        r.bottom -= (psbi->dxyLineButton);
    }
    else
    {
        if (thumbPos)
            thumbPos += pcontext->wi.rcClient.left - pcontext->wi.rcWindow.left;
        r.left  += psbi->dxyLineButton;
        r.right -= psbi->dxyLineButton;
    }

    if (r.right <= r.left || r.bottom <= r.top)
        return;

    /* Draw the scroll rectangles and thumb */

    if (!thumbPos)  /* No thumb to draw */
    {
        rcPart = r;
        SCROLL_ThemeDrawPart(pcontext, vertical ? SBP_UPPERTRACKVERT: SBP_UPPERTRACKHORZ , BUTTON_NORMAL, psbi, SCROLL_THUMB, 0, 0, &rcPart);
        return;
    }

    /* Some themes have different bitmaps for the upper and lower tracks  
       It seems that windows use the bitmap for the lower track in the upper track */
    if (vertical)
    { 
        rcPart = r;
        rcPart.bottom = thumbPos;
        SCROLL_ThemeDrawPart(pcontext, SBP_LOWERTRACKVERT, BUTTON_NORMAL, psbi, SCROLL_TOP_RECT, htDown, htHot, &rcPart);
        r.top = rcPart.bottom;

        rcPart = r;
        rcPart.top += psbi->xyThumbBottom - psbi->xyThumbTop;
        SCROLL_ThemeDrawPart(pcontext, SBP_UPPERTRACKVERT, BUTTON_NORMAL, psbi, SCROLL_BOTTOM_RECT, htDown, htHot, &rcPart); 
        r.bottom = rcPart.top;

        SCROLL_ThemeDrawPart(pcontext, SBP_THUMBBTNVERT, BUTTON_NORMAL, psbi, SCROLL_THUMB, htDown, htHot, &r); 
        SCROLL_ThemeDrawPart(pcontext, SBP_GRIPPERVERT, BUTTON_NORMAL, psbi, SCROLL_THUMB, htDown, htHot, &r); 
    }
    else  /* horizontal */
    {
        rcPart = r;
        rcPart.right = thumbPos;
        SCROLL_ThemeDrawPart(pcontext, SBP_LOWERTRACKHORZ, BUTTON_NORMAL, psbi, SCROLL_TOP_RECT, htDown, htHot, &rcPart);
        r.left = rcPart.right;

        rcPart = r;
        rcPart.left += psbi->xyThumbBottom - psbi->xyThumbTop;
        SCROLL_ThemeDrawPart(pcontext, SBP_UPPERTRACKHORZ, BUTTON_NORMAL, psbi, SCROLL_BOTTOM_RECT, htDown, htHot, &rcPart);
        r.right = rcPart.left;

        SCROLL_ThemeDrawPart(pcontext, SBP_THUMBBTNHORZ, BUTTON_NORMAL, psbi, SCROLL_THUMB, htDown, htHot, &r);
        SCROLL_ThemeDrawPart(pcontext, SBP_GRIPPERHORZ, BUTTON_NORMAL, psbi, SCROLL_THUMB, htDown, htHot, &r);
    }
}
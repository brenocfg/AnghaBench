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
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_17__ {scalar_t__ left; scalar_t__ right; int bottom; int top; } ;
struct TYPE_14__ {scalar_t__ right; scalar_t__ top; int bottom; scalar_t__ left; } ;
struct TYPE_16__ {int fStatus; int fDraw; scalar_t__ cxHeader; int fStyle; scalar_t__ cyChild; scalar_t__ cxIdeal; scalar_t__ hwndChild; TYPE_2__ rcBand; TYPE_6__ rcChild; TYPE_6__ rcChevron; TYPE_6__ rcCapText; TYPE_6__ rcCapImage; TYPE_6__ rcGripper; } ;
struct TYPE_13__ {scalar_t__ cx; int cy; } ;
struct TYPE_15__ {scalar_t__ hwndSelf; TYPE_1__ imageSize; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ REBAR_INFO ;
typedef  TYPE_4__ REBAR_BAND ;

/* Variables and functions */
 scalar_t__ CHEVRON_WIDTH ; 
 int DRAW_GRIPPER ; 
 int DRAW_IMAGE ; 
 int DRAW_TEXT ; 
 scalar_t__ GRIPPER_WIDTH ; 
 int HAS_GRIPPER ; 
 int HAS_IMAGE ; 
 int HAS_TEXT ; 
 scalar_t__ HIDDENBAND (TYPE_4__*) ; 
 int /*<<< orphan*/  InflateRect (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int NTF_INVALIDATE ; 
 int RBBS_HIDETITLE ; 
 int RBBS_USECHEVRON ; 
 scalar_t__ REBAR_ALWAYS_SPACE ; 
 TYPE_4__* REBAR_GetBand (TYPE_3__ const*,scalar_t__) ; 
 scalar_t__ REBAR_POST_CHILD ; 
 scalar_t__ REBAR_POST_IMAGE ; 
 scalar_t__ REBAR_POST_TEXT ; 
 scalar_t__ REBAR_PRE_GRIPPER ; 
 scalar_t__ SEP_WIDTH ; 
 int /*<<< orphan*/  SetRect (TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_2__*) ; 

__attribute__((used)) static void
REBAR_CalcHorzBand (const REBAR_INFO *infoPtr, UINT rstart, UINT rend)
     /* Function: this routine initializes all the rectangles in */
     /*  each band in a row to fit in the adjusted rcBand rect.  */
     /* *** Supports only Horizontal bars. ***                   */
{
    REBAR_BAND *lpBand;
    UINT i, xoff;
    RECT work;

    for(i=rstart; i<rend; i++){
      lpBand = REBAR_GetBand(infoPtr, i);
      if (HIDDENBAND(lpBand)) {
          SetRect (&lpBand->rcChild,
		   lpBand->rcBand.right, lpBand->rcBand.top,
		   lpBand->rcBand.right, lpBand->rcBand.bottom);
	  continue;
      }

      /* set initial gripper rectangle */
      SetRect (&lpBand->rcGripper, lpBand->rcBand.left, lpBand->rcBand.top,
	       lpBand->rcBand.left, lpBand->rcBand.bottom);

      /* calculate gripper rectangle */
      if ( lpBand->fStatus & HAS_GRIPPER) {
	  lpBand->fDraw |= DRAW_GRIPPER;
	  lpBand->rcGripper.left   += REBAR_PRE_GRIPPER;
	  lpBand->rcGripper.right  = lpBand->rcGripper.left + GRIPPER_WIDTH;
          InflateRect(&lpBand->rcGripper, 0, -2);

	  SetRect (&lpBand->rcCapImage,
		   lpBand->rcGripper.right+REBAR_ALWAYS_SPACE, lpBand->rcBand.top,
		   lpBand->rcGripper.right+REBAR_ALWAYS_SPACE, lpBand->rcBand.bottom);
      }
      else {  /* no gripper will be drawn */
	  xoff = 0;
	  if (lpBand->fStatus & (HAS_IMAGE | HAS_TEXT))
	      /* if no gripper but either image or text, then leave space */
	      xoff = REBAR_ALWAYS_SPACE;
	  SetRect (&lpBand->rcCapImage,
		   lpBand->rcBand.left+xoff, lpBand->rcBand.top,
		   lpBand->rcBand.left+xoff, lpBand->rcBand.bottom);
      }

      /* image is visible */
      if (lpBand->fStatus & HAS_IMAGE) {
	  lpBand->fDraw |= DRAW_IMAGE;
	  lpBand->rcCapImage.right  += infoPtr->imageSize.cx;
	  lpBand->rcCapImage.bottom = lpBand->rcCapImage.top + infoPtr->imageSize.cy;

	  /* set initial caption text rectangle */
	  SetRect (&lpBand->rcCapText,
		   lpBand->rcCapImage.right+REBAR_POST_IMAGE, lpBand->rcBand.top+1,
		   lpBand->rcBand.left+lpBand->cxHeader, lpBand->rcBand.bottom-1);
      }
      else {
	  /* set initial caption text rectangle */
	  SetRect (&lpBand->rcCapText, lpBand->rcCapImage.right, lpBand->rcBand.top+1,
		   lpBand->rcBand.left+lpBand->cxHeader, lpBand->rcBand.bottom-1);
      }

      /* text is visible */
      if ((lpBand->fStatus & HAS_TEXT) && !(lpBand->fStyle & RBBS_HIDETITLE)) {
	  lpBand->fDraw |= DRAW_TEXT;
	  lpBand->rcCapText.right = max(lpBand->rcCapText.left,
					lpBand->rcCapText.right-REBAR_POST_TEXT);
      }

      /* set initial child window rectangle if there is a child */
      if (lpBand->hwndChild) {

          lpBand->rcChild.left  = lpBand->rcBand.left + lpBand->cxHeader;
          lpBand->rcChild.right = lpBand->rcBand.right - REBAR_POST_CHILD;

          if (lpBand->cyChild > 0) {

              UINT yoff = (lpBand->rcBand.bottom - lpBand->rcBand.top - lpBand->cyChild) / 2;

              /* center child if height is known */
              lpBand->rcChild.top = lpBand->rcBand.top + yoff;
              lpBand->rcChild.bottom = lpBand->rcBand.top + yoff + lpBand->cyChild;
          }
          else {
              lpBand->rcChild.top = lpBand->rcBand.top;
              lpBand->rcChild.bottom = lpBand->rcBand.bottom;
          }

	  if ((lpBand->fStyle & RBBS_USECHEVRON) && (lpBand->rcChild.right - lpBand->rcChild.left < lpBand->cxIdeal))
	  {
	      lpBand->rcChild.right -= CHEVRON_WIDTH;
	      SetRect(&lpBand->rcChevron, lpBand->rcChild.right,
	              lpBand->rcChild.top, lpBand->rcChild.right + CHEVRON_WIDTH,
	              lpBand->rcChild.bottom);
	  }
      }
      else {
          SetRect (&lpBand->rcChild,
		   lpBand->rcBand.left+lpBand->cxHeader, lpBand->rcBand.top,
		   lpBand->rcBand.right, lpBand->rcBand.bottom);
      }

      /* flag if notify required and invalidate rectangle */
      if (lpBand->fDraw & NTF_INVALIDATE) {
	  lpBand->fDraw &= ~NTF_INVALIDATE;
	  work = lpBand->rcBand;
	  work.right += SEP_WIDTH;
	  work.bottom += SEP_WIDTH;
	  TRACE("invalidating %s\n", wine_dbgstr_rect(&work));
	  InvalidateRect(infoPtr->hwndSelf, &work, TRUE);
	  if (lpBand->hwndChild) InvalidateRect(lpBand->hwndChild, NULL, TRUE);
      }

    }

}
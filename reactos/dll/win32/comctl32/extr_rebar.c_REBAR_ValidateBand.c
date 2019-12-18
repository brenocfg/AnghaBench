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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int fStatus; int cxMinChild; int cyMinChild; int cx; int cyChild; int cyIntegral; int cxIdeal; int cxHeader; int fStyle; int iImage; int fMask; scalar_t__ cxMinBand; int /*<<< orphan*/  cyHeader; scalar_t__ lpText; scalar_t__ cyMinBand; } ;
struct TYPE_13__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_15__ {scalar_t__ uNumBands; int dwStyle; int /*<<< orphan*/  hFont; TYPE_1__ imageSize; scalar_t__ himl; } ;
struct TYPE_14__ {scalar_t__ cy; scalar_t__ cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ REBAR_INFO ;
typedef  TYPE_4__ REBAR_BAND ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int CCS_VERT ; 
 scalar_t__ CHEVRON_WIDTH ; 
 scalar_t__ GRIPPER_HEIGHT ; 
 scalar_t__ GRIPPER_WIDTH ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int HAS_GRIPPER ; 
 int HAS_IMAGE ; 
 int HAS_TEXT ; 
 int /*<<< orphan*/  HIDDENBAND (TYPE_4__*) ; 
 int RBBIM_TEXT ; 
 int RBBS_FIXEDSIZE ; 
 int RBBS_GRIPPERALWAYS ; 
 int RBBS_HIDETITLE ; 
 int RBBS_NOGRIPPER ; 
 int RBBS_UNDOC_FIXEDHEADER ; 
 int RBBS_USECHEVRON ; 
 int RBS_VERTICALGRIPPER ; 
 scalar_t__ REBAR_ALWAYS_SPACE ; 
 TYPE_4__* REBAR_GetBand (TYPE_3__ const*,scalar_t__) ; 
 scalar_t__ REBAR_POST_CHILD ; 
 scalar_t__ REBAR_POST_IMAGE ; 
 scalar_t__ REBAR_POST_TEXT ; 
 scalar_t__ REBAR_PRE_GRIPPER ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  update_min_band_height (TYPE_3__ const*,TYPE_4__*) ; 

__attribute__((used)) static VOID
REBAR_ValidateBand (const REBAR_INFO *infoPtr, REBAR_BAND *lpBand)
     /* Function:  This routine evaluates the band specs supplied */
     /*  by the user and updates the following 5 fields in        */
     /*  the internal band structure: cxHeader, cyHeader, cxMinBand, cyMinBand, fStatus */
{
    UINT header=0;
    UINT textheight=0, imageheight = 0;
    UINT i, nonfixed;
    REBAR_BAND *tBand;

    lpBand->fStatus = 0;
    lpBand->cxMinBand = 0;
    lpBand->cyMinBand = 0;

    /* Data coming in from users into the cx... and cy... fields   */
    /* may be bad, just garbage, because the user never clears     */
    /* the fields. RB_{SET|INSERT}BAND{A|W} just passes the data   */
    /* along if the fields exist in the input area. Here we must   */
    /* determine if the data is valid. I have no idea how MS does  */
    /* the validation, but it does because the RB_GETBANDINFO      */
    /* returns a 0 when I know the sample program passed in an     */
    /* address. Here I will use the algorithm that if the value    */
    /* is greater than 65535 then it is bad and replace it with    */
    /* a zero. Feel free to improve the algorithm.  -  GA 12/2000  */
    if (lpBand->cxMinChild > 65535) lpBand->cxMinChild = 0;
    if (lpBand->cyMinChild > 65535) lpBand->cyMinChild = 0;
    if (lpBand->cx         > 65535) lpBand->cx         = 0;
    if (lpBand->cyChild    > 65535) lpBand->cyChild    = 0;
    if (lpBand->cyIntegral > 65535) lpBand->cyIntegral = 0;
    if (lpBand->cxIdeal    > 65535) lpBand->cxIdeal    = 0;
    if (lpBand->cxHeader   > 65535) lpBand->cxHeader   = 0;

    /* TODO : we could try return to the caller if a value changed so that */
    /*        a REBAR_Layout is needed. Till now the caller should call it */
    /*        it always (we should also check what native does)            */

    /* Header is where the image, text and gripper exist  */
    /* in the band and precede the child window.          */

    /* count number of non-FIXEDSIZE and non-Hidden bands */
    nonfixed = 0;
    for (i=0; i<infoPtr->uNumBands; i++){
	tBand = REBAR_GetBand(infoPtr, i);
	if (!HIDDENBAND(tBand) && !(tBand->fStyle & RBBS_FIXEDSIZE))
	    nonfixed++;
    }

    /* calculate gripper rectangle */
    if (  (!(lpBand->fStyle & RBBS_NOGRIPPER)) &&
	  ( (lpBand->fStyle & RBBS_GRIPPERALWAYS) ||
	    ( !(lpBand->fStyle & RBBS_FIXEDSIZE) && (nonfixed > 1)))
       ) {
	lpBand->fStatus |= HAS_GRIPPER;
        if (infoPtr->dwStyle & CCS_VERT)
	    if (infoPtr->dwStyle & RBS_VERTICALGRIPPER)
                header += (GRIPPER_HEIGHT + REBAR_PRE_GRIPPER);
            else
	        header += (GRIPPER_WIDTH + REBAR_PRE_GRIPPER);
        else
            header += (REBAR_PRE_GRIPPER + GRIPPER_WIDTH);
        /* Always have 4 pixels before anything else */
        header += REBAR_ALWAYS_SPACE;
    }

    /* image is visible */
    if (lpBand->iImage != -1 && (infoPtr->himl)) {
	lpBand->fStatus |= HAS_IMAGE;
        if (infoPtr->dwStyle & CCS_VERT) {
	   header += (infoPtr->imageSize.cy + REBAR_POST_IMAGE);
           imageheight = infoPtr->imageSize.cx + 4;
	}
	else {
	   header += (infoPtr->imageSize.cx + REBAR_POST_IMAGE);
           imageheight = infoPtr->imageSize.cy + 4;
	}
    }

    /* text is visible */
    if ((lpBand->fMask & RBBIM_TEXT) && (lpBand->lpText) &&
        !(lpBand->fStyle & RBBS_HIDETITLE)) {
	HDC hdc = GetDC (0);
	HFONT hOldFont = SelectObject (hdc, infoPtr->hFont);
	SIZE size;

	lpBand->fStatus |= HAS_TEXT;
	GetTextExtentPoint32W (hdc, lpBand->lpText,
			       lstrlenW (lpBand->lpText), &size);
	header += ((infoPtr->dwStyle & CCS_VERT) ? (size.cy + REBAR_POST_TEXT) : (size.cx + REBAR_POST_TEXT));
	textheight = (infoPtr->dwStyle & CCS_VERT) ? 0 : size.cy;

	SelectObject (hdc, hOldFont);
	ReleaseDC (0, hdc);
    }

    /* if no gripper but either image or text, then leave space */
    if ((lpBand->fStatus & (HAS_IMAGE | HAS_TEXT)) &&
	!(lpBand->fStatus & HAS_GRIPPER)) {
	header += REBAR_ALWAYS_SPACE;
    }

    /* check if user overrode the header value */
    if (!(lpBand->fStyle & RBBS_UNDOC_FIXEDHEADER))
        lpBand->cxHeader = header;
    lpBand->cyHeader = max(textheight, imageheight);

    /* Now compute minimum size of child window */
    update_min_band_height(infoPtr, lpBand);       /* update lpBand->cyMinBand from cyHeader and cyChild*/

    lpBand->cxMinBand = lpBand->cxMinChild + lpBand->cxHeader + REBAR_POST_CHILD;
    if (lpBand->fStyle & RBBS_USECHEVRON && lpBand->cxMinChild < lpBand->cxIdeal)
        lpBand->cxMinBand += CHEVRON_WIDTH;
}
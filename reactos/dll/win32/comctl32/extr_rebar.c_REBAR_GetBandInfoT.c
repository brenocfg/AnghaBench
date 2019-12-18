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
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ cbSize; int fMask; int fStyle; scalar_t__ clrBack; int /*<<< orphan*/  cxHeader; int /*<<< orphan*/  lParam; int /*<<< orphan*/  cxIdeal; int /*<<< orphan*/  wID; int /*<<< orphan*/  hbmBack; int /*<<< orphan*/  cx; int /*<<< orphan*/  cyIntegral; int /*<<< orphan*/  cyMaxChild; int /*<<< orphan*/  cyChild; int /*<<< orphan*/  cyMinChild; int /*<<< orphan*/  cxMinChild; int /*<<< orphan*/  hwndChild; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cch; scalar_t__ lpText; int /*<<< orphan*/  clrFore; } ;
struct TYPE_10__ {int fStyle; scalar_t__ clrBack; int /*<<< orphan*/  cxHeader; int /*<<< orphan*/  lParam; int /*<<< orphan*/  cxIdeal; int /*<<< orphan*/  wID; int /*<<< orphan*/  hbmBack; int /*<<< orphan*/  cx; int /*<<< orphan*/  cyIntegral; int /*<<< orphan*/  cyMaxChild; int /*<<< orphan*/  cyChild; int /*<<< orphan*/  cyMinChild; int /*<<< orphan*/  cxMinChild; int /*<<< orphan*/  hwndChild; int /*<<< orphan*/  iImage; int /*<<< orphan*/  lpText; int /*<<< orphan*/  clrFore; } ;
struct TYPE_9__ {scalar_t__ uNumBands; scalar_t__ clrBtnFace; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_3__* LPREBARBANDINFOW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CLR_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int RBBIM_BACKGROUND ; 
 int RBBIM_CHILD ; 
 int RBBIM_CHILDSIZE ; 
 int RBBIM_COLORS ; 
 int RBBIM_HEADERSIZE ; 
 int RBBIM_ID ; 
 int RBBIM_IDEALSIZE ; 
 int RBBIM_IMAGE ; 
 int RBBIM_LPARAM ; 
 int RBBIM_SIZE ; 
 int RBBIM_STYLE ; 
 int RBBIM_TEXT ; 
 int RBBS_VARIABLEHEIGHT ; 
 scalar_t__ REBARBANDINFOA_V3_SIZE ; 
 scalar_t__ REBARBANDINFOW_V6_SIZE ; 
 int /*<<< orphan*/  REBAR_DumpBandInfo (TYPE_3__*) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  Str_GetPtrW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_GetPtrWtoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_GetBandInfoT(const REBAR_INFO *infoPtr, UINT uIndex, LPREBARBANDINFOW lprbbi, BOOL bUnicode)
{
    REBAR_BAND *lpBand;

    if (!lprbbi || lprbbi->cbSize < REBARBANDINFOA_V3_SIZE)
	return FALSE;

    if (uIndex >= infoPtr->uNumBands)
	return FALSE;

    TRACE("index %u (bUnicode=%d)\n", uIndex, bUnicode);

    /* copy band information */
    lpBand = REBAR_GetBand(infoPtr, uIndex);

    if (lprbbi->fMask & RBBIM_STYLE)
	lprbbi->fStyle = lpBand->fStyle;

    if (lprbbi->fMask & RBBIM_COLORS) {
	lprbbi->clrFore = lpBand->clrFore;
	lprbbi->clrBack = lpBand->clrBack;
	if (lprbbi->clrBack == CLR_DEFAULT)
	    lprbbi->clrBack = infoPtr->clrBtnFace;
    }

    if (lprbbi->fMask & RBBIM_TEXT) {
        if (bUnicode)
            Str_GetPtrW(lpBand->lpText, lprbbi->lpText, lprbbi->cch);
        else
            Str_GetPtrWtoA(lpBand->lpText, (LPSTR)lprbbi->lpText, lprbbi->cch);
    }

    if (lprbbi->fMask & RBBIM_IMAGE)
	lprbbi->iImage = lpBand->iImage;

    if (lprbbi->fMask & RBBIM_CHILD)
	lprbbi->hwndChild = lpBand->hwndChild;

    if (lprbbi->fMask & RBBIM_CHILDSIZE) {
	lprbbi->cxMinChild = lpBand->cxMinChild;
	lprbbi->cyMinChild = lpBand->cyMinChild;
        /* to make tests pass we follow Windows' behaviour and allow reading these fields only
         * for RBBS_VARIABLEHEIGHTS bands */
        if (lprbbi->cbSize >= REBARBANDINFOW_V6_SIZE && (lpBand->fStyle & RBBS_VARIABLEHEIGHT)) {
	    lprbbi->cyChild    = lpBand->cyChild;
	    lprbbi->cyMaxChild = lpBand->cyMaxChild;
	    lprbbi->cyIntegral = lpBand->cyIntegral;
	}
    }

    if (lprbbi->fMask & RBBIM_SIZE)
	lprbbi->cx = lpBand->cx;

    if (lprbbi->fMask & RBBIM_BACKGROUND)
	lprbbi->hbmBack = lpBand->hbmBack;

    if (lprbbi->fMask & RBBIM_ID)
	lprbbi->wID = lpBand->wID;

    /* check for additional data */
    if (lprbbi->cbSize >= REBARBANDINFOW_V6_SIZE) {
	if (lprbbi->fMask & RBBIM_IDEALSIZE)
	    lprbbi->cxIdeal = lpBand->cxIdeal;

	if (lprbbi->fMask & RBBIM_LPARAM)
	    lprbbi->lParam = lpBand->lParam;

	if (lprbbi->fMask & RBBIM_HEADERSIZE)
	    lprbbi->cxHeader = lpBand->cxHeader;
    }

    REBAR_DumpBandInfo(lprbbi);

    return TRUE;
}
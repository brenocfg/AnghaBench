#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ cbSize; int fMask; scalar_t__ lpText; } ;
struct TYPE_20__ {scalar_t__ clrFore; scalar_t__ clrBack; int iImage; int fStyle; int cyMaxChild; int /*<<< orphan*/  lpText; scalar_t__ cyIntegral; int /*<<< orphan*/  cyMinChild; int /*<<< orphan*/  cyChild; } ;
struct TYPE_19__ {int uNumBands; scalar_t__ clrText; scalar_t__ clrBtnText; scalar_t__ clrBk; scalar_t__ clrBtnFace; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bands; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  TYPE_3__ REBARBANDINFOW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 TYPE_2__* Alloc (int) ; 
 scalar_t__ CLR_NONE ; 
 int DPA_InsertPtr (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RBBIM_TEXT ; 
 int RBBS_VARIABLEHEIGHT ; 
 scalar_t__ REBARBANDINFOA_V3_SIZE ; 
 scalar_t__ REBARBANDINFOA_V6_SIZE ; 
 int /*<<< orphan*/  REBAR_CommonSetupBand (int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  REBAR_DumpBand (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_DumpBandInfo (TYPE_3__ const*) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_ValidateBand (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Str_SetPtrAtoW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrW (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT
REBAR_InsertBandT(REBAR_INFO *infoPtr, INT iIndex, const REBARBANDINFOW *lprbbi, BOOL bUnicode)
{
    REBAR_BAND *lpBand;

    if (!lprbbi || lprbbi->cbSize < REBARBANDINFOA_V3_SIZE)
	return FALSE;

    /* trace the index as signed to see the -1 */
    TRACE("insert band at %d (bUnicode=%d)!\n", iIndex, bUnicode);
    REBAR_DumpBandInfo(lprbbi);

    if (!(lpBand = Alloc(sizeof(REBAR_BAND)))) return FALSE;
    if ((iIndex == -1) || (iIndex > infoPtr->uNumBands))
        iIndex = infoPtr->uNumBands;
    if (DPA_InsertPtr(infoPtr->bands, iIndex, lpBand) == -1)
    {
        Free(lpBand);
        return FALSE;
    }
    infoPtr->uNumBands++;

    TRACE("index %d!\n", iIndex);

    /* initialize band */
    memset(lpBand, 0, sizeof(*lpBand));
    lpBand->clrFore = infoPtr->clrText == CLR_NONE ? infoPtr->clrBtnText :
                                                     infoPtr->clrText;
    lpBand->clrBack = infoPtr->clrBk == CLR_NONE ? infoPtr->clrBtnFace :
                                                   infoPtr->clrBk;
    lpBand->iImage = -1;

    REBAR_CommonSetupBand(infoPtr->hwndSelf, lprbbi, lpBand);

    /* Make sure the defaults for these are correct */
    if (lprbbi->cbSize < REBARBANDINFOA_V6_SIZE || !(lpBand->fStyle & RBBS_VARIABLEHEIGHT)) {
        lpBand->cyChild    = lpBand->cyMinChild;
        lpBand->cyMaxChild = 0x7fffffff;
        lpBand->cyIntegral = 0;
    }

    if ((lprbbi->fMask & RBBIM_TEXT) && (lprbbi->lpText)) {
        if (bUnicode)
            Str_SetPtrW(&lpBand->lpText, lprbbi->lpText);
        else
            Str_SetPtrAtoW(&lpBand->lpText, (LPSTR)lprbbi->lpText);
    }

    REBAR_ValidateBand (infoPtr, lpBand);
    /* On insert of second band, revalidate band 1 to possible add gripper */
    if (infoPtr->uNumBands == 2)
	REBAR_ValidateBand (infoPtr, REBAR_GetBand(infoPtr, 0));

    REBAR_DumpBand (infoPtr);

    REBAR_Layout(infoPtr);
    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);

    return TRUE;
}
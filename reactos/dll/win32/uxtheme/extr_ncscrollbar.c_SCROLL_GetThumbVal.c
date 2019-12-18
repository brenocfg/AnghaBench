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
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_5__ {scalar_t__ nMin; scalar_t__ nPage; scalar_t__ nMax; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ MulDiv (scalar_t__,scalar_t__,scalar_t__) ; 
 int SCROLL_ARROW_THUMB_OVERLAP ; 
 scalar_t__ SCROLL_MIN_THUMB ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static UINT SCROLL_GetThumbVal( SCROLLINFO *psi, RECT *rect,
                                  BOOL vertical, INT pos )
{
    INT thumbSize;
    INT pixels = vertical ? rect->bottom-rect->top : rect->right-rect->left;
    INT range;

    if ((pixels -= 2*(GetSystemMetrics(SM_CXVSCROLL) - SCROLL_ARROW_THUMB_OVERLAP)) <= 0)
        return psi->nMin;

    if (psi->nPage)
    {
        thumbSize = MulDiv(pixels,psi->nPage,(psi->nMax-psi->nMin+1));
        if (thumbSize < SCROLL_MIN_THUMB) thumbSize = SCROLL_MIN_THUMB;
    }
    else thumbSize = GetSystemMetrics(SM_CXVSCROLL);

    if ((pixels -= thumbSize) <= 0) return psi->nMin;

    pos = max( 0, pos - (GetSystemMetrics(SM_CXVSCROLL) - SCROLL_ARROW_THUMB_OVERLAP) );
    if (pos > pixels) pos = pixels;

    if (!psi->nPage)
        range = psi->nMax - psi->nMin;
    else
        range = psi->nMax - psi->nMin - psi->nPage + 1;

    return psi->nMin + MulDiv(pos, range, pixels);
}
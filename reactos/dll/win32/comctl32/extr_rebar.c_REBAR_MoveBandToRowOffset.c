#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fStyle; int cxMinBand; scalar_t__ cxEffective; } ;
struct TYPE_8__ {int iGrabbedBand; int /*<<< orphan*/  bands; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPA_DeletePtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPA_InsertPtr (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int RBBS_BREAK ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__*,int) ; 
 scalar_t__ SEP_WIDTH ; 
 int next_visible (TYPE_1__*,int) ; 

__attribute__((used)) static int REBAR_MoveBandToRowOffset(REBAR_INFO *infoPtr, INT iBand, INT iFirstBand,
    INT iLastBand, INT xOff, BOOL reorder)
{
    REBAR_BAND *insertBand = REBAR_GetBand(infoPtr, iBand);
    int xPos = 0, i;
    const BOOL setBreak = REBAR_GetBand(infoPtr, iFirstBand)->fStyle & RBBS_BREAK;

    /* Find the band's new position */
    if(reorder)
    {
        /* Used during an LR band reorder drag */
        for (i = iFirstBand; i < iLastBand; i = next_visible(infoPtr, i))
        {
            if(xPos > xOff)
                break;
            xPos += REBAR_GetBand(infoPtr, i)->cxEffective + SEP_WIDTH;
        }
    }
    else
    {
        /* Used during a UD band insertion drag */
        for (i = iFirstBand; i < iLastBand; i = next_visible(infoPtr, i))
        {
            const REBAR_BAND *band = REBAR_GetBand(infoPtr, i);
            if(xPos + band->cxMinBand / 2 > xOff)
                break;
            xPos += band->cxEffective + SEP_WIDTH;
        }
    }

    /* Move the band to its new position */
    DPA_DeletePtr(infoPtr->bands, iBand);
    if(i > iBand)
        i--;
    DPA_InsertPtr(infoPtr->bands, i, insertBand);

    /* Ensure only the last band has the RBBS_BREAK flag set */
    insertBand->fStyle &= ~RBBS_BREAK;
    if(setBreak)
        REBAR_GetBand(infoPtr, iFirstBand)->fStyle |= RBBS_BREAK;

    /* Return the currently grabbed band */
    if(infoPtr->iGrabbedBand == iBand)
    {
        infoPtr->iGrabbedBand = i;
        return i;
    }
    else return -1;
}
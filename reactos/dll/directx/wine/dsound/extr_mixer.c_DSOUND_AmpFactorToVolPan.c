#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dwTotalLeftAmpFactor; scalar_t__ dwTotalRightAmpFactor; double lVolume; scalar_t__ dwVolAmpFactor; double lPan; } ;
typedef  TYPE_1__* PDSVOLUMEPAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int log (int) ; 

void DSOUND_AmpFactorToVolPan(PDSVOLUMEPAN volpan)
{
    double left,right;
    TRACE("(%p)\n",volpan);

    TRACE("left=%x, right=%x\n",volpan->dwTotalLeftAmpFactor,volpan->dwTotalRightAmpFactor);
    if (volpan->dwTotalLeftAmpFactor==0)
        left=-10000;
    else
        left=600 * log(((double)volpan->dwTotalLeftAmpFactor) / 0xffff) / log(2);
    if (volpan->dwTotalRightAmpFactor==0)
        right=-10000;
    else
        right=600 * log(((double)volpan->dwTotalRightAmpFactor) / 0xffff) / log(2);
    if (left<right)
    {
        volpan->lVolume=right;
        volpan->dwVolAmpFactor=volpan->dwTotalRightAmpFactor;
    }
    else
    {
        volpan->lVolume=left;
        volpan->dwVolAmpFactor=volpan->dwTotalLeftAmpFactor;
    }
    if (volpan->lVolume < -10000)
        volpan->lVolume=-10000;
    volpan->lPan=right-left;
    if (volpan->lPan < -10000)
        volpan->lPan=-10000;

    TRACE("Vol=%d Pan=%d\n", volpan->lVolume, volpan->lPan);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int left; int top; int right; long bottom; } ;
struct TYPE_6__ {int top; int bottom; } ;
struct TYPE_7__ {int m_nShiftPixels; int m_nPlotShiftPixels; int* m_dPreviousPosition; int m_dLowerLimit; int m_dVerticalFactor; int m_nHalfShiftPixels; int* m_dCurrentPosition; int /*<<< orphan*/  m_brushBack; int /*<<< orphan*/ * m_dcPlot; TYPE_3__ m_rectPlot; TYPE_1__ m_rectClient; scalar_t__* m_penPlot; int /*<<< orphan*/  m_nPlotHeight; int /*<<< orphan*/  m_nPlotWidth; } ;
typedef  TYPE_2__ TGraphCtrl ;
typedef  TYPE_3__ RECT ;
typedef  scalar_t__ HPEN ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ *,int,int) ; 
 int MAX_PLOTS ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ *,scalar_t__) ; 

void GraphCtrl_DrawPoint(TGraphCtrl* this)
{
    /*  this does the work of "scrolling" the plot to the left
     *  and appending a new data point all of the plotting is
     *  directed to the memory based bitmap associated with m_dcPlot
     *  the will subsequently be BitBlt'd to the client in Paint
     */
    int currX, prevX, currY, prevY;
    HPEN oldPen;
    RECT rectCleanUp;
    int i;

    if (this->m_dcPlot != NULL)
    {
        /*  shift the plot by BitBlt'ing it to itself
         *  note: the m_dcPlot covers the entire client
         *        but we only shift bitmap that is the size
         *        of the plot rectangle
         *  grab the right side of the plot (excluding m_nShiftPixels on the left)
         *  move this grabbed bitmap to the left by m_nShiftPixels
         */
        BitBlt(this->m_dcPlot, this->m_rectPlot.left, this->m_rectPlot.top+1,
               this->m_nPlotWidth, this->m_nPlotHeight, this->m_dcPlot,
               this->m_rectPlot.left+this->m_nShiftPixels, this->m_rectPlot.top+1,
               SRCCOPY);

        /*  establish a rectangle over the right side of plot */
        /*  which now needs to be cleaned up prior to adding the new point */
        rectCleanUp = this->m_rectPlot;
        rectCleanUp.left  = rectCleanUp.right - this->m_nShiftPixels;

        /*  fill the cleanup area with the background */
        FillRect(this->m_dcPlot, &rectCleanUp, this->m_brushBack);

        /*  draw the next line segment */
        for (i = 0; i < MAX_PLOTS; i++)
        {
            /*  grab the plotting pen */
            oldPen = (HPEN)SelectObject(this->m_dcPlot, this->m_penPlot[i]);

            /*  move to the previous point */
            prevX = this->m_rectPlot.right-this->m_nPlotShiftPixels;
            prevY = this->m_rectPlot.bottom -
                (long)((this->m_dPreviousPosition[i] - this->m_dLowerLimit) * this->m_dVerticalFactor);
            MoveToEx(this->m_dcPlot, prevX, prevY, NULL);

            /*  draw to the current point */
            currX = this->m_rectPlot.right-this->m_nHalfShiftPixels;
            currY = this->m_rectPlot.bottom -
                (long)((this->m_dCurrentPosition[i] - this->m_dLowerLimit) * this->m_dVerticalFactor);
            LineTo(this->m_dcPlot, currX, currY);

            /*  Restore the pen  */
            SelectObject(this->m_dcPlot, oldPen);

            /*  if the data leaks over the upper or lower plot boundaries
             *  fill the upper and lower leakage with the background
             *  this will facilitate clipping on an as needed basis
             *  as opposed to always calling IntersectClipRect
             */
            if ((prevY <= this->m_rectPlot.top) || (currY <= this->m_rectPlot.top))
            {
                RECT rc;
                rc.bottom = this->m_rectPlot.top+1;
                rc.left = prevX;
                rc.right = currX+1;
                rc.top = this->m_rectClient.top;
                FillRect(this->m_dcPlot, &rc, this->m_brushBack);
            }
            if ((prevY >= this->m_rectPlot.bottom) || (currY >= this->m_rectPlot.bottom))
            {
                RECT rc;
                rc.bottom = this->m_rectClient.bottom+1;
                rc.left = prevX;
                rc.right = currX+1;
                rc.top = this->m_rectPlot.bottom+1;
                /* RECT rc(prevX, m_rectPlot.bottom+1, currX+1, m_rectClient.bottom+1); */
                FillRect(this->m_dcPlot, &rc, this->m_brushBack);
            }

            /*  store the current point for connection to the next point */
            this->m_dPreviousPosition[i] = this->m_dCurrentPosition[i];
        }
    }
}
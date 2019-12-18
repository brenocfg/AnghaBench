#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_5__ {int left; int top; scalar_t__ right; scalar_t__ bottom; } ;
struct TYPE_6__ {double m_dVerticalFactor; double m_dRange; scalar_t__ m_nPlotHeight; TYPE_1__ m_rectPlot; scalar_t__ m_nPlotWidth; TYPE_4__ m_rectClient; scalar_t__ m_nClientWidth; scalar_t__ m_nClientHeight; int /*<<< orphan*/  m_hWnd; } ;
typedef  TYPE_2__ TGraphCtrl ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_4__*) ; 

void GraphCtrl_Resize(TGraphCtrl* this)
{
    /*  NOTE: Resize automatically gets called during the setup of the control */
    GetClientRect(this->m_hWnd, &this->m_rectClient);

    /*  set some member variables to avoid multiple function calls */
    this->m_nClientHeight = this->m_rectClient.bottom - this->m_rectClient.top;/* m_rectClient.Height(); */
    this->m_nClientWidth  = this->m_rectClient.right - this->m_rectClient.left;/* m_rectClient.Width(); */

    /*  the "left" coordinate and "width" will be modified in  */
    /*  InvalidateCtrl to be based on the width of the y axis scaling */
#if 0
    this->m_rectPlot.left   = 20;
    this->m_rectPlot.top    = 10;
    this->m_rectPlot.right  = this->m_rectClient.right-10;
    this->m_rectPlot.bottom = this->m_rectClient.bottom-25;
#else
    this->m_rectPlot.left   = 0;
    this->m_rectPlot.top    = -1;
    this->m_rectPlot.right  = this->m_rectClient.right-0;
    this->m_rectPlot.bottom = this->m_rectClient.bottom-0;
#endif

    /*  set some member variables to avoid multiple function calls */
    this->m_nPlotHeight = this->m_rectPlot.bottom - this->m_rectPlot.top;/* m_rectPlot.Height(); */
    this->m_nPlotWidth  = this->m_rectPlot.right - this->m_rectPlot.left;/* m_rectPlot.Width(); */

    /*  set the scaling factor for now, this can be adjusted  */
    /*  in the SetRange functions */
    this->m_dVerticalFactor = (double)this->m_nPlotHeight / this->m_dRange;
}
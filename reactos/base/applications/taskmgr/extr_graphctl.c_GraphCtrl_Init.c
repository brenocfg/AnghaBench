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
struct TYPE_3__ {double* m_dPreviousPosition; int m_nYDecimals; double m_dLowerLimit; double m_dUpperLimit; double m_dRange; int m_nShiftPixels; int m_nHalfShiftPixels; int m_nPlotShiftPixels; int /*<<< orphan*/ * m_bitmapOldPlot; int /*<<< orphan*/ * m_bitmapOldGrid; int /*<<< orphan*/  m_strYUnitsString; int /*<<< orphan*/  m_strXUnitsString; void* m_crBackColor; scalar_t__ m_brushBack; void** m_crPlotColor; int /*<<< orphan*/ * m_penPlot; void* m_crGridColor; scalar_t__ m_bitmapPlot; scalar_t__ m_bitmapGrid; scalar_t__ m_dcPlot; scalar_t__ m_dcGrid; scalar_t__ m_hParentWnd; scalar_t__ m_hWnd; } ;
typedef  TYPE_1__ TGraphCtrl ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ CreateSolidBrush (void*) ; 
 int MAX_PLOTS ; 
 int /*<<< orphan*/  PS_SOLID ; 
 void* RGB (int,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void GraphCtrl_Init(TGraphCtrl* this)
{
    int i;

    this->m_hWnd = 0;
    this->m_hParentWnd = 0;
    this->m_dcGrid = 0;
    this->m_dcPlot = 0;
    this->m_bitmapOldGrid = 0;
    this->m_bitmapOldPlot = 0;
    this->m_bitmapGrid = 0;
    this->m_bitmapPlot = 0;
    this->m_brushBack = 0;

    this->m_penPlot[0] = 0;
    this->m_penPlot[1] = 0;
    this->m_penPlot[2] = 0;
    this->m_penPlot[3] = 0;

    /* since plotting is based on a LineTo for each new point
     * we need a starting point (i.e. a "previous" point)
     * use 0.0 as the default first point.
     * these are public member variables, and can be changed outside
     * (after construction).  Therefore m_perviousPosition could be set to
     * a more appropriate value prior to the first call to SetPosition.
     */
    this->m_dPreviousPosition[0] = 0.0;
    this->m_dPreviousPosition[1] = 0.0;
    this->m_dPreviousPosition[2] = 0.0;
    this->m_dPreviousPosition[3] = 0.0;

    /*  public variable for the number of decimal places on the y axis */
    this->m_nYDecimals = 3;

    /*  set some initial values for the scaling until "SetRange" is called.
     *  these are protected variables and must be set with SetRange
     *  in order to ensure that m_dRange is updated accordingly
     */
    /*   m_dLowerLimit = -10.0; */
    /*   m_dUpperLimit =  10.0; */
    this->m_dLowerLimit = 0.0;
    this->m_dUpperLimit = 100.0;
    this->m_dRange      =  this->m_dUpperLimit - this->m_dLowerLimit;   /*  protected member variable */

    /*  m_nShiftPixels determines how much the plot shifts (in terms of pixels)  */
    /*  with the addition of a new data point */
    this->m_nShiftPixels     = 4;
    this->m_nHalfShiftPixels = this->m_nShiftPixels/2;                     /*  protected */
    this->m_nPlotShiftPixels = this->m_nShiftPixels + this->m_nHalfShiftPixels;  /*  protected */

    /*  background, grid and data colors */
    /*  these are public variables and can be set directly */
    this->m_crBackColor = RGB(  0,   0,   0);  /*  see also SetBackgroundColor */
    this->m_crGridColor = RGB(  0, 128, 64);  /*  see also SetGridColor */
    this->m_crPlotColor[0] = RGB(255, 255, 255);  /*  see also SetPlotColor */
    this->m_crPlotColor[1] = RGB(100, 255, 255);  /*  see also SetPlotColor */
    this->m_crPlotColor[2] = RGB(255, 100, 255);  /*  see also SetPlotColor */
    this->m_crPlotColor[3] = RGB(255, 255, 100);  /*  see also SetPlotColor */

    /*  protected variables */
    for (i = 0; i < MAX_PLOTS; i++)
    {
        this->m_penPlot[i] = CreatePen(PS_SOLID, 0, this->m_crPlotColor[i]);
    }
    this->m_brushBack = CreateSolidBrush(this->m_crBackColor);

    /*  public member variables, can be set directly  */
    strcpy(this->m_strXUnitsString, "Samples");  /*  can also be set with SetXUnits */
    strcpy(this->m_strYUnitsString, "Y units");  /*  can also be set with SetYUnits */

    /*  protected bitmaps to restore the memory DC's */
    this->m_bitmapOldGrid = NULL;
    this->m_bitmapOldPlot = NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int left; } ;
struct TYPE_11__ {int left; } ;
struct TYPE_10__ {int left; int top; int bottom; int right; } ;
struct TYPE_8__ {int left; int right; int top; int bottom; } ;
struct TYPE_9__ {int m_nYDecimals; int m_nPlotWidth; int /*<<< orphan*/  m_hParentWnd; TYPE_5__ m_rectClient; int /*<<< orphan*/  m_brushBack; int /*<<< orphan*/ * m_dcPlot; int /*<<< orphan*/  m_crBackColor; int /*<<< orphan*/ * m_bitmapPlot; int /*<<< orphan*/  m_nClientHeight; int /*<<< orphan*/  m_nClientWidth; int /*<<< orphan*/ * m_bitmapOldPlot; int /*<<< orphan*/ * m_dcGrid; TYPE_1__ m_rectPlot; int /*<<< orphan*/  m_dLowerLimit; int /*<<< orphan*/  m_dUpperLimit; int /*<<< orphan*/ * m_bitmapGrid; int /*<<< orphan*/ * m_bitmapOldGrid; int /*<<< orphan*/  m_crGridColor; } ;
typedef  TYPE_2__ TGraphCtrl ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  void* HBITMAP ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 void* CreateCompatibleBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateFont (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * CreatePen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FF_SWISS ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextAlign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TA_BASELINE ; 
 int TA_CENTER ; 
 int TA_LEFT ; 
 int TA_RIGHT ; 
 int TA_TOP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ *,int,int,char*,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/ * axisFont ; 
 int /*<<< orphan*/  fabs (int /*<<< orphan*/ ) ; 
 scalar_t__ log10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_crGridColor ; 
 int /*<<< orphan*/  m_dLowerLimit ; 
 int /*<<< orphan*/  m_dUpperLimit ; 
 int /*<<< orphan*/ * m_dcGrid ; 
 int m_nPlotWidth ; 
 int m_nShiftPixels ; 
 int /*<<< orphan*/  m_nYDecimals ; 
 TYPE_4__ m_rectClient ; 
 TYPE_3__ m_rectPlot ; 
 char* m_strXUnitsString ; 
 char* m_strYUnitsString ; 
 int max (int,int) ; 
 int /*<<< orphan*/ * oldFont ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 char* strTemp ; 
 int wcslen (char*) ; 
 int /*<<< orphan*/ * yUnitFont ; 

void GraphCtrl_InvalidateCtrl(TGraphCtrl* this, BOOL bResize)
{
    /*  There is a lot of drawing going on here - particularly in terms of  */
    /*  drawing the grid.  Don't panic, this is all being drawn (only once) */
    /*  to a bitmap.  The result is then BitBlt'd to the control whenever needed. */
    int i;
    int nCharacters;
    //int nTopGridPix, nMidGridPix, nBottomGridPix;

    HPEN oldPen;
    HPEN solidPen = CreatePen(PS_SOLID, 0, this->m_crGridColor);
    /* HFONT axisFont, yUnitFont, oldFont; */
    /* char strTemp[50]; */

    /*  in case we haven't established the memory dc's */
    /* CClientDC dc(this); */
    HDC dc = GetDC(this->m_hParentWnd);

    /*  if we don't have one yet, set up a memory dc for the grid */
    if (this->m_dcGrid == NULL)
    {
        this->m_dcGrid = CreateCompatibleDC(dc);
        this->m_bitmapGrid = CreateCompatibleBitmap(dc, this->m_nClientWidth, this->m_nClientHeight);
        this->m_bitmapOldGrid = (HBITMAP)SelectObject(this->m_dcGrid, this->m_bitmapGrid);
    }
    else if(bResize)
    {
        // the size of the drawing area has changed
        // so create a new bitmap of the appropriate size
        if(this->m_bitmapGrid != NULL)
        {
            this->m_bitmapGrid = (HBITMAP)SelectObject(this->m_dcGrid, this->m_bitmapOldGrid);
            DeleteObject(this->m_bitmapGrid);
            this->m_bitmapGrid = CreateCompatibleBitmap(dc, this->m_nClientWidth, this->m_nClientHeight);
            SelectObject(this->m_dcGrid, this->m_bitmapGrid);
        }
    }

    SetBkColor(this->m_dcGrid, this->m_crBackColor);

    /*  fill the grid background */
    FillRect(this->m_dcGrid, &this->m_rectClient, this->m_brushBack);

    /*  draw the plot rectangle: */
    /*  determine how wide the y axis scaling values are */
    nCharacters = abs((int)log10(fabs(this->m_dUpperLimit)));
    nCharacters = max(nCharacters, abs((int)log10(fabs(this->m_dLowerLimit))));

    /*  add the units digit, decimal point and a minus sign, and an extra space */
    /*  as well as the number of decimal places to display */
    nCharacters = nCharacters + 4 + this->m_nYDecimals;

    /*  adjust the plot rectangle dimensions */
    /*  assume 6 pixels per character (this may need to be adjusted) */
    /*   m_rectPlot.left = m_rectClient.left + 6*(nCharacters); */
    this->m_rectPlot.left = this->m_rectClient.left;
    this->m_nPlotWidth    = this->m_rectPlot.right - this->m_rectPlot.left;/* m_rectPlot.Width(); */

    /*  draw the plot rectangle */
    oldPen = (HPEN)SelectObject(this->m_dcGrid, solidPen);
    MoveToEx(this->m_dcGrid, this->m_rectPlot.left, this->m_rectPlot.top, NULL);
    LineTo(this->m_dcGrid, this->m_rectPlot.right+1, this->m_rectPlot.top);
    LineTo(this->m_dcGrid, this->m_rectPlot.right+1, this->m_rectPlot.bottom+1);
    LineTo(this->m_dcGrid, this->m_rectPlot.left, this->m_rectPlot.bottom+1);
    /*   LineTo(m_dcGrid, m_rectPlot.left, m_rectPlot.top); */

    /*  draw the horizontal axis */
    for (i = this->m_rectPlot.top; i < this->m_rectPlot.bottom; i += 12)
    {
        MoveToEx(this->m_dcGrid, this->m_rectPlot.left, this->m_rectPlot.top + i, NULL);
        LineTo(this->m_dcGrid, this->m_rectPlot.right, this->m_rectPlot.top + i);
    }

    /*  draw the vertical axis */
    for (i = this->m_rectPlot.left; i < this->m_rectPlot.right; i += 12)
    {
        MoveToEx(this->m_dcGrid, this->m_rectPlot.left + i, this->m_rectPlot.bottom, NULL);
        LineTo(this->m_dcGrid, this->m_rectPlot.left + i, this->m_rectPlot.top);
    }

    SelectObject(this->m_dcGrid, oldPen);
    DeleteObject(solidPen);

#if 0
    /*  create some fonts (horizontal and vertical) */
    /*  use a height of 14 pixels and 300 weight  */
    /*  (these may need to be adjusted depending on the display) */
    axisFont = CreateFont (14, 0, 0, 0, 300,
                           FALSE, FALSE, 0, ANSI_CHARSET,
                           OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY,
                           DEFAULT_PITCH|FF_SWISS, "Arial");
    yUnitFont = CreateFont (14, 0, 900, 0, 300,
                            FALSE, FALSE, 0, ANSI_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH|FF_SWISS, "Arial");

    /*  grab the horizontal font */
    oldFont = (HFONT)SelectObject(m_dcGrid, axisFont);

    /*  y max */
    SetTextColor(m_dcGrid, m_crGridColor);
    SetTextAlign(m_dcGrid, TA_RIGHT|TA_TOP);
    sprintf(strTemp, "%.*lf", m_nYDecimals, m_dUpperLimit);
    TextOut(m_dcGrid, m_rectPlot.left-4, m_rectPlot.top, strTemp, wcslen(strTemp));

    /*  y min */
    SetTextAlign(m_dcGrid, TA_RIGHT|TA_BASELINE);
    sprintf(strTemp, "%.*lf", m_nYDecimals, m_dLowerLimit);
    TextOut(m_dcGrid, m_rectPlot.left-4, m_rectPlot.bottom, strTemp, wcslen(strTemp));

    /*  x min */
    SetTextAlign(m_dcGrid, TA_LEFT|TA_TOP);
    TextOut(m_dcGrid, m_rectPlot.left, m_rectPlot.bottom+4, "0", 1);

    /*  x max */
    SetTextAlign(m_dcGrid, TA_RIGHT|TA_TOP);
    sprintf(strTemp, "%d", m_nPlotWidth/m_nShiftPixels);
    TextOut(m_dcGrid, m_rectPlot.right, m_rectPlot.bottom+4, strTemp, wcslen(strTemp));

    /*  x units */
    SetTextAlign(m_dcGrid, TA_CENTER|TA_TOP);
    TextOut(m_dcGrid, (m_rectPlot.left+m_rectPlot.right)/2,
            m_rectPlot.bottom+4, m_strXUnitsString, wcslen(m_strXUnitsString));

    /*  restore the font */
    SelectObject(m_dcGrid, oldFont);

    /*  y units */
    oldFont = (HFONT)SelectObject(m_dcGrid, yUnitFont);
    SetTextAlign(m_dcGrid, TA_CENTER|TA_BASELINE);
    TextOut(m_dcGrid, (m_rectClient.left+m_rectPlot.left)/2,
            (m_rectPlot.bottom+m_rectPlot.top)/2, m_strYUnitsString, wcslen(m_strYUnitsString));
    SelectObject(m_dcGrid, oldFont);
#endif
    /*  at this point we are done filling the grid bitmap,  */
    /*  no more drawing to this bitmap is needed until the settings are changed */

    /*  if we don't have one yet, set up a memory dc for the plot */
    if (this->m_dcPlot == NULL)
    {
        this->m_dcPlot = CreateCompatibleDC(dc);
        this->m_bitmapPlot = CreateCompatibleBitmap(dc, this->m_nClientWidth, this->m_nClientHeight);
        this->m_bitmapOldPlot = (HBITMAP)SelectObject(this->m_dcPlot, this->m_bitmapPlot);
    }
    else if(bResize)
    {
        // the size of the drawing area has changed
        // so create a new bitmap of the appropriate size
        if(this->m_bitmapPlot != NULL)
        {
            this->m_bitmapPlot = (HBITMAP)SelectObject(this->m_dcPlot, this->m_bitmapOldPlot);
            DeleteObject(this->m_bitmapPlot);
            this->m_bitmapPlot = CreateCompatibleBitmap(dc, this->m_nClientWidth, this->m_nClientHeight);
            SelectObject(this->m_dcPlot, this->m_bitmapPlot);
        }
    }

    /*  make sure the plot bitmap is cleared */
    SetBkColor(this->m_dcPlot, this->m_crBackColor);
    FillRect(this->m_dcPlot, &this->m_rectClient, this->m_brushBack);

    /*  finally, force the plot area to redraw */
    InvalidateRect(this->m_hParentWnd, &this->m_rectClient, TRUE);
    ReleaseDC(this->m_hParentWnd, dc);
}
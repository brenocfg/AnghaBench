#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cy; int cx; } ;
struct TYPE_9__ {int cxLeftWidth; int cxRightWidth; scalar_t__ cyTopHeight; scalar_t__ cyBottomHeight; } ;
struct TYPE_8__ {int cy; int cx; } ;
struct TYPE_10__ {int dwStyle; int nBitmapHeight; int nBitmapWidth; int iListGap; TYPE_2__ themeMargins; TYPE_1__ szPadding; } ;
typedef  TYPE_3__ TOOLBAR_INFO ;
typedef  TYPE_4__ SIZE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DEFPAD_CY ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int LISTPAD_CY ; 
 scalar_t__ NONLIST_NOTEXT_OFFSET ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int TBSTYLE_LIST ; 
 void* max (int,int) ; 

__attribute__((used)) static inline SIZE TOOLBAR_MeasureButton(const TOOLBAR_INFO *infoPtr, SIZE sizeString,
                                         BOOL bHasBitmap, BOOL bValidImageList)
{
    SIZE sizeButton;
    if (infoPtr->dwStyle & TBSTYLE_LIST)
    {
        /* set button height from bitmap / text height... */
        sizeButton.cy = max((bHasBitmap ? infoPtr->nBitmapHeight : 0),
            sizeString.cy);

        /* ... add on the necessary padding */
        if (bValidImageList)
        {
#ifdef __REACTOS__
            sizeButton.cy += infoPtr->szPadding.cy;
            if (!bHasBitmap)
#else
            if (bHasBitmap)
                sizeButton.cy += DEFPAD_CY;
            else
#endif
                sizeButton.cy += LISTPAD_CY;
        }
        else
            sizeButton.cy += infoPtr->szPadding.cy;

        /* calculate button width */
        sizeButton.cx = 2*GetSystemMetrics(SM_CXEDGE) +
            infoPtr->nBitmapWidth + infoPtr->iListGap;
        if (sizeString.cx > 0)
            sizeButton.cx += sizeString.cx + infoPtr->szPadding.cx;

    }
    else
    {
        if (bHasBitmap)
        {
#ifdef __REACTOS__
            sizeButton.cy = infoPtr->nBitmapHeight + infoPtr->szPadding.cy;
#else
            sizeButton.cy = infoPtr->nBitmapHeight + DEFPAD_CY;
#endif
            if (sizeString.cy > 0)
                sizeButton.cy += 1 + sizeString.cy;
            sizeButton.cx = infoPtr->szPadding.cx +
                max(sizeString.cx, infoPtr->nBitmapWidth);
        }
        else
        {
            sizeButton.cy = sizeString.cy + infoPtr->szPadding.cy +
                NONLIST_NOTEXT_OFFSET;
            sizeButton.cx = infoPtr->szPadding.cx +
                max(2*GetSystemMetrics(SM_CXEDGE) + sizeString.cx, infoPtr->nBitmapWidth);
        }
    }

#ifdef __REACTOS__
    sizeButton.cx += infoPtr->themeMargins.cxLeftWidth + infoPtr->themeMargins.cxRightWidth;
    sizeButton.cy += infoPtr->themeMargins.cyTopHeight + infoPtr->themeMargins.cyBottomHeight;
#endif

    return sizeButton;
}
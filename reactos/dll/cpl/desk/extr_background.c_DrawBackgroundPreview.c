#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_17__ {int /*<<< orphan*/  desktop_color; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_16__ {TYPE_1__ rcItem; int /*<<< orphan*/  hDC; } ;
struct TYPE_15__ {size_t backgroundSelection; int placementSelection; int /*<<< orphan*/  cySource; int /*<<< orphan*/  cxSource; TYPE_3__* pWallpaperBitmap; TYPE_2__* backgroundItems; int /*<<< orphan*/  hBitmap; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {float width; float height; int /*<<< orphan*/  info; int /*<<< orphan*/  bits; } ;
struct TYPE_12__ {scalar_t__ bWallpaper; } ;
typedef  TYPE_4__ RECT ;
typedef  TYPE_5__* PBACKGROUND_DATA ;
typedef  TYPE_6__* LPDRAWITEMSTRUCT ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  COLORONCOLOR ; 
 int /*<<< orphan*/  COLOR_BACKGROUND ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdiTransparentBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONITOR_BOTTOM ; 
 int MONITOR_HEIGHT ; 
 int /*<<< orphan*/  MONITOR_LEFT ; 
 int /*<<< orphan*/  MONITOR_RIGHT ; 
 int /*<<< orphan*/  MONITOR_TOP ; 
 int MONITOR_WIDTH ; 
 int MulDiv (int,int,int) ; 
#define  PLACEMENT_CENTER 132 
#define  PLACEMENT_FILL 131 
#define  PLACEMENT_FIT 130 
#define  PLACEMENT_STRETCH 129 
#define  PLACEMENT_TILE 128 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetStretchBltMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StretchDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ g_GlobalData ; 

__attribute__((used)) static VOID
DrawBackgroundPreview(LPDRAWITEMSTRUCT draw, PBACKGROUND_DATA pData)
{
    float scaleX;
    float scaleY;
    int scaledWidth;
    int scaledHeight;
    int posX, desX;
    int posY, desY;
    int fitFillScaleNum, fitFillScaleDen;
    int fitFillWidth, fitFillHeight;
    HBRUSH hBrush;
    int x;
    int y;
    HDC hDC;
    HGDIOBJ hOldObj;
    RECT rcItem = {
        MONITOR_LEFT,
        MONITOR_TOP,
        MONITOR_RIGHT,
        MONITOR_BOTTOM
    };

    hDC = CreateCompatibleDC(draw->hDC);
    hOldObj = SelectObject(hDC, pData->hBitmap);

    if (pData->backgroundItems[pData->backgroundSelection].bWallpaper == FALSE)
    {
        /* Update desktop background color image */
        hBrush = CreateSolidBrush(g_GlobalData.desktop_color);
        FillRect(hDC, &rcItem, hBrush);
        DeleteObject(hBrush);
    }
    else
    if (pData->pWallpaperBitmap != NULL)
    {
        scaleX = ((float)GetSystemMetrics(SM_CXSCREEN) - 1) / (float)MONITOR_WIDTH;
        scaleY = ((float)GetSystemMetrics(SM_CYSCREEN) - 1) / (float)MONITOR_HEIGHT;

        scaledWidth = (int)(pData->pWallpaperBitmap->width / scaleX);
        scaledHeight = (int)(pData->pWallpaperBitmap->height / scaleY);

        FillRect(hDC, &rcItem, GetSysColorBrush(COLOR_BACKGROUND));

        SetStretchBltMode(hDC, COLORONCOLOR);

        switch (pData->placementSelection)
        {
            case PLACEMENT_CENTER:
                posX = (MONITOR_WIDTH - scaledWidth + 1) / 2;
                posY = (MONITOR_HEIGHT - scaledHeight + 1) / 2;
                desX = 0;
                desY = 0;

                if (posX < 0) { desX = -posX / 2; posX = 0; }
                if (posY < 0) { desY = -posY / 2; posY = 0; }

                if (scaledWidth > MONITOR_WIDTH)
                    scaledWidth = MONITOR_WIDTH;

                if (scaledHeight > MONITOR_HEIGHT)
                    scaledHeight = MONITOR_HEIGHT;

                StretchDIBits(hDC,
                              MONITOR_LEFT+posX,
                              MONITOR_TOP+posY,
                              scaledWidth,
                              scaledHeight,
                              desX,
                              desY,
                              pData->pWallpaperBitmap->width - (int)(desX * scaleX),
                              pData->pWallpaperBitmap->height - (int)(desY * scaleY),
                              pData->pWallpaperBitmap->bits,
                              pData->pWallpaperBitmap->info,
                              DIB_RGB_COLORS,
                              SRCCOPY);
                break;

            case PLACEMENT_STRETCH:
                StretchDIBits(hDC,
                              MONITOR_LEFT,
                              MONITOR_TOP,
                              MONITOR_WIDTH,
                              MONITOR_HEIGHT,
                              0,
                              0,
                              pData->pWallpaperBitmap->width,
                              pData->pWallpaperBitmap->height,
                              pData->pWallpaperBitmap->bits,
                              pData->pWallpaperBitmap->info,
                              DIB_RGB_COLORS,
                              SRCCOPY);
                break;

            case PLACEMENT_TILE:
                for (y = 0; y < MONITOR_HEIGHT; y += scaledHeight)
                {
                    for (x = 0; x < MONITOR_WIDTH; x += scaledWidth)
                    {
                        if ((MONITOR_WIDTH-x) >= scaledWidth)
                            posX = scaledWidth;
                        else
                            posX = MONITOR_WIDTH-x;


                        if ((MONITOR_HEIGHT-y) >= scaledHeight)
                            posY = scaledHeight;
                        else
                            posY = MONITOR_HEIGHT-y;

                        StretchDIBits(hDC,
                                      MONITOR_LEFT + x,
                                      MONITOR_TOP + y,
                                      posX,
                                      posY,
                                      0,
                                      0,
                                      pData->pWallpaperBitmap->width * posX / scaledWidth,
                                      pData->pWallpaperBitmap->height * posY / scaledHeight,
                                      pData->pWallpaperBitmap->bits,
                                      pData->pWallpaperBitmap->info,
                                      DIB_RGB_COLORS,
                                      SRCCOPY);
                    }

                }

                break;

            case PLACEMENT_FIT:
                if ((MONITOR_WIDTH * scaledHeight) <= (MONITOR_HEIGHT * scaledWidth))
                {
                    fitFillScaleNum = MONITOR_WIDTH;
                    fitFillScaleDen = scaledWidth;
                }
                else
                {
                    fitFillScaleNum = MONITOR_HEIGHT;
                    fitFillScaleDen = scaledHeight;
                }

                fitFillWidth = MulDiv(scaledWidth, fitFillScaleNum, fitFillScaleDen);
                fitFillHeight = MulDiv(scaledHeight, fitFillScaleNum, fitFillScaleDen);

                posX = (MONITOR_WIDTH - fitFillWidth) / 2;
                posY = (MONITOR_HEIGHT - fitFillHeight) / 2;

                StretchDIBits(hDC,
                              MONITOR_LEFT + posX,
                              MONITOR_TOP + posY,
                              fitFillWidth,
                              fitFillHeight,
                              0,
                              0,
                              pData->pWallpaperBitmap->width,
                              pData->pWallpaperBitmap->height,
                              pData->pWallpaperBitmap->bits,
                              pData->pWallpaperBitmap->info,
                              DIB_RGB_COLORS,
                              SRCCOPY);
                break;

            case PLACEMENT_FILL:
                if ((MONITOR_WIDTH * scaledHeight) > (MONITOR_HEIGHT * scaledWidth))
                {
                    fitFillScaleNum = MONITOR_WIDTH;
                    fitFillScaleDen = scaledWidth;
                }
                else
                {
                    fitFillScaleNum = MONITOR_HEIGHT;
                    fitFillScaleDen = scaledHeight;
                }

                fitFillWidth = MulDiv(scaledWidth, fitFillScaleNum, fitFillScaleDen);
                fitFillHeight = MulDiv(scaledHeight, fitFillScaleNum, fitFillScaleDen);

                desX = (((fitFillWidth - MONITOR_WIDTH) * pData->pWallpaperBitmap->width) / (2 * fitFillWidth));
                desY = (((fitFillHeight - MONITOR_HEIGHT) * pData->pWallpaperBitmap->height) / (2 * fitFillHeight));

                StretchDIBits(hDC,
                              MONITOR_LEFT,
                              MONITOR_TOP,
                              MONITOR_WIDTH,
                              MONITOR_HEIGHT,
                              desX,
                              desY,
                              (MONITOR_WIDTH * pData->pWallpaperBitmap->width) / fitFillWidth,
                              (MONITOR_HEIGHT * pData->pWallpaperBitmap->height) / fitFillHeight,
                              pData->pWallpaperBitmap->bits,
                              pData->pWallpaperBitmap->info,
                              DIB_RGB_COLORS,
                              SRCCOPY);
                break;
        }
    }

    GdiTransparentBlt(draw->hDC,
                      draw->rcItem.left, draw->rcItem.top,
                      draw->rcItem.right-draw->rcItem.left+1,
                      draw->rcItem.bottom-draw->rcItem.top+1,
                      hDC,
                      0, 0,
                      pData->cxSource, pData->cySource,
                      0xFF00FF);

    SelectObject(hDC, hOldObj);
    DeleteDC(hDC);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t uNumItem; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/ * hFont; TYPE_2__* items; int /*<<< orphan*/  bRectsValid; } ;
struct TYPE_8__ {int right; int bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_9__ {TYPE_1__ rect; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int LRESULT ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  TYPE_2__ HEADER_ITEM ;
typedef  TYPE_3__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CDDS_POSTPAINT ; 
 int /*<<< orphan*/  CDDS_PREPAINT ; 
 int CDRF_NOTIFYPOSTPAINT ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_DrawItem (TYPE_3__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int HEADER_SendCtrlCustomDraw (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEADER_SetItemBounds (TYPE_3__*) ; 
 int /*<<< orphan*/  ILC_COLORDDB ; 
 int /*<<< orphan*/  ImageList_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ImageList_Create (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HIMAGELIST
HEADER_CreateDragImage (HEADER_INFO *infoPtr, INT iItem)
{
    HEADER_ITEM *lpItem;
    HIMAGELIST himl;
    HBITMAP hMemory, hOldBitmap;
    LRESULT lCDFlags;
    RECT rc;
    HDC hMemoryDC;
    HDC hDeviceDC;
    int height, width;
    HFONT hFont;
    
    if (iItem >= infoPtr->uNumItem)
        return NULL;

    if (!infoPtr->bRectsValid)
        HEADER_SetItemBounds(infoPtr);

    lpItem = &infoPtr->items[iItem];
    width = lpItem->rect.right - lpItem->rect.left;
    height = lpItem->rect.bottom - lpItem->rect.top;
    
    hDeviceDC = GetDC(NULL);
    hMemoryDC = CreateCompatibleDC(hDeviceDC);
    hMemory = CreateCompatibleBitmap(hDeviceDC, width, height);
    ReleaseDC(NULL, hDeviceDC);
    hOldBitmap = SelectObject(hMemoryDC, hMemory);
    SetViewportOrgEx(hMemoryDC, -lpItem->rect.left, -lpItem->rect.top, NULL);
    hFont = infoPtr->hFont ? infoPtr->hFont : GetStockObject(SYSTEM_FONT);
    SelectObject(hMemoryDC, hFont);

    GetClientRect(infoPtr->hwndSelf, &rc);
    lCDFlags = HEADER_SendCtrlCustomDraw(infoPtr, CDDS_PREPAINT, hMemoryDC, &rc);
    HEADER_DrawItem(infoPtr, hMemoryDC, iItem, FALSE, lCDFlags);
    if (lCDFlags & CDRF_NOTIFYPOSTPAINT)
        HEADER_SendCtrlCustomDraw(infoPtr, CDDS_POSTPAINT, hMemoryDC, &rc);
    
    hMemory = SelectObject(hMemoryDC, hOldBitmap);
    DeleteDC(hMemoryDC);
    
    if (hMemory == NULL)    /* if anything failed */
        return NULL;

    himl = ImageList_Create(width, height, ILC_COLORDDB, 1, 1);
    ImageList_Add(himl, hMemory, NULL);
    DeleteObject(hMemory);
    return himl;
}
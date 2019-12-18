#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct RtfData {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
struct TYPE_7__ {TYPE_4__ bmiHeader; TYPE_1__* bmiColors; } ;
struct TYPE_6__ {int rgbRed; int rgbGreen; int rgbBlue; } ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int BOOL ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBM_INIT ; 
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDIBitmap (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,void const*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEnhMetaFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetEnhMetaFileBits (int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HLPFILE_RtfAddControl (struct RtfData*,char*) ; 
 scalar_t__ HLPFILE_RtfAddHexBytes (struct RtfData*,void*,scalar_t__) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCAND ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SRCPAINT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL HLPFILE_RtfAddTransparentBitmap(struct RtfData* rd, const BITMAPINFO* bi,
                                            const void* pict, unsigned nc)
{
    HDC                 hdc, hdcMask, hdcMem, hdcEMF;
    HBITMAP             hbm, hbmMask, hbmOldMask, hbmOldMem;
    HENHMETAFILE        hEMF;
    BOOL                ret = FALSE;
    void*               data;
    UINT                sz;

    hbm = CreateDIBitmap(hdc = GetDC(0), &bi->bmiHeader,
                         CBM_INIT, pict, bi, DIB_RGB_COLORS);

    hdcMem = CreateCompatibleDC(hdc);
    hbmOldMem = SelectObject(hdcMem, hbm);

    /* create the mask bitmap from the main bitmap */
    hdcMask = CreateCompatibleDC(hdc);
    hbmMask = CreateBitmap(bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, 1, 1, NULL);
    hbmOldMask = SelectObject(hdcMask, hbmMask);
    SetBkColor(hdcMem,
               RGB(bi->bmiColors[nc - 1].rgbRed,
                   bi->bmiColors[nc - 1].rgbGreen,
                   bi->bmiColors[nc - 1].rgbBlue));
    BitBlt(hdcMask, 0, 0, bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, hdcMem, 0, 0, SRCCOPY);

    /* sets to RGB(0,0,0) the transparent bits in main bitmap */
    SetBkColor(hdcMem, RGB(0,0,0));
    SetTextColor(hdcMem, RGB(255,255,255));
    BitBlt(hdcMem, 0, 0, bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, hdcMask, 0, 0, SRCAND);

    SelectObject(hdcMask, hbmOldMask);
    DeleteDC(hdcMask);

    SelectObject(hdcMem, hbmOldMem);
    DeleteDC(hdcMem);

    /* we create the bitmap on the fly */
    hdcEMF = CreateEnhMetaFileW(NULL, NULL, NULL, NULL);
    hdcMem = CreateCompatibleDC(hdcEMF);

    /* sets to RGB(0,0,0) the transparent bits in final bitmap */
    hbmOldMem = SelectObject(hdcMem, hbmMask);
    SetBkColor(hdcEMF, RGB(255, 255, 255));
    SetTextColor(hdcEMF, RGB(0, 0, 0));
    BitBlt(hdcEMF, 0, 0, bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, hdcMem, 0, 0, SRCAND);

    /* and copy the remaining bits of main bitmap */
    SelectObject(hdcMem, hbm);
    BitBlt(hdcEMF, 0, 0, bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, hdcMem, 0, 0, SRCPAINT);
    SelectObject(hdcMem, hbmOldMem);
    DeleteDC(hdcMem);

    /* do the cleanup */
    ReleaseDC(0, hdc);
    DeleteObject(hbmMask);
    DeleteObject(hbm);

    hEMF = CloseEnhMetaFile(hdcEMF);

    /* generate rtf stream */
    sz = GetEnhMetaFileBits(hEMF, 0, NULL);
    if (sz && (data = HeapAlloc(GetProcessHeap(), 0, sz)))
    {
        if (sz == GetEnhMetaFileBits(hEMF, sz, data))
        {
            ret = HLPFILE_RtfAddControl(rd, "{\\pict\\emfblip") &&
                HLPFILE_RtfAddHexBytes(rd, data, sz) &&
                HLPFILE_RtfAddControl(rd, "}");
        }
        HeapFree(GetProcessHeap(), 0, data);
    }
    DeleteEnhMetaFile(hEMF);

    return ret;
}
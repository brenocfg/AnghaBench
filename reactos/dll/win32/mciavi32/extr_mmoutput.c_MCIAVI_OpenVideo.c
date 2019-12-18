#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fccHandler; } ;
struct TYPE_9__ {int dwCachedFrame; scalar_t__ hWndPaint; TYPE_7__* outbih; TYPE_5__* inbih; int /*<<< orphan*/  hic; void* outdata; TYPE_1__ ash_video; } ;
typedef  TYPE_2__ WINE_MCIAVI ;
struct TYPE_11__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biCompression; int biSizeImage; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int biClrImportant; } ;
struct TYPE_10__ {scalar_t__ biCompression; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int LPSTR ;
typedef  int HDC ;
typedef  scalar_t__ FOURCC ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 scalar_t__ BI_RGB ; 
 scalar_t__ BI_RLE4 ; 
 scalar_t__ BI_RLE8 ; 
 int /*<<< orphan*/  FALSE ; 
 int GetDC (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  ICGetDisplayFormat (int /*<<< orphan*/ ,TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICLocate (int /*<<< orphan*/ ,scalar_t__,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMODE_DECOMPRESS ; 
 int /*<<< orphan*/  ICM_DECOMPRESS_BEGIN ; 
 scalar_t__ ICSendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICTYPE_VIDEO ; 
 int /*<<< orphan*/  MCIAVI_PaintFrame (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ mmioFOURCC (char,char,char,char) ; 

BOOL    MCIAVI_OpenVideo(WINE_MCIAVI* wma)
{
    HDC hDC;
    DWORD	outSize;
    FOURCC	fcc = wma->ash_video.fccHandler;

    TRACE("fcc %4.4s\n", (LPSTR)&fcc);

    wma->dwCachedFrame = -1;

    /* get the right handle */
    if (fcc == mmioFOURCC('C','R','A','M')) fcc = mmioFOURCC('M','S','V','C');

    /* try to get a decompressor for that type */
    wma->hic = ICLocate(ICTYPE_VIDEO, fcc, wma->inbih, NULL, ICMODE_DECOMPRESS);
    if (!wma->hic) {
        /* check for builtin DIB compressions */
        fcc = wma->inbih->biCompression;
        if ((fcc == mmioFOURCC('D','I','B',' ')) ||
            (fcc == mmioFOURCC('R','L','E',' ')) ||
            (fcc == BI_RGB) || (fcc == BI_RLE8) ||
            (fcc == BI_RLE4) || (fcc == BI_BITFIELDS))
            goto paint_frame;

	WARN("Can't locate codec for the file\n");
	return FALSE;
    }

    outSize = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);

    wma->outbih = HeapAlloc(GetProcessHeap(), 0, outSize);
    if (!wma->outbih) {
	WARN("Can't alloc output BIH\n");
	return FALSE;
    }
    if (!ICGetDisplayFormat(wma->hic, wma->inbih, wma->outbih, 0, 0, 0)) {
	WARN("Can't open decompressor\n");
	return FALSE;
    }

    TRACE("bih.biSize=%d\n", 		wma->outbih->biSize);
    TRACE("bih.biWidth=%d\n", 		wma->outbih->biWidth);
    TRACE("bih.biHeight=%d\n", 	wma->outbih->biHeight);
    TRACE("bih.biPlanes=%d\n", 		wma->outbih->biPlanes);
    TRACE("bih.biBitCount=%d\n", 	wma->outbih->biBitCount);
    TRACE("bih.biCompression=%x\n", 	wma->outbih->biCompression);
    TRACE("bih.biSizeImage=%d\n", 	wma->outbih->biSizeImage);
    TRACE("bih.biXPelsPerMeter=%d\n", 	wma->outbih->biXPelsPerMeter);
    TRACE("bih.biYPelsPerMeter=%d\n", 	wma->outbih->biYPelsPerMeter);
    TRACE("bih.biClrUsed=%d\n", 	wma->outbih->biClrUsed);
    TRACE("bih.biClrImportant=%d\n", 	wma->outbih->biClrImportant);

    wma->outdata = HeapAlloc(GetProcessHeap(), 0, wma->outbih->biSizeImage);
    if (!wma->outdata) {
	WARN("Can't alloc output buffer\n");
	return FALSE;
    }

    if (ICSendMessage(wma->hic, ICM_DECOMPRESS_BEGIN,
		      (DWORD_PTR)wma->inbih, (DWORD_PTR)wma->outbih) != ICERR_OK) {
	WARN("Can't begin decompression\n");
	return FALSE;
    }

paint_frame:
    hDC = wma->hWndPaint ? GetDC(wma->hWndPaint) : 0;
    if (hDC)
    {
        MCIAVI_PaintFrame(wma, hDC);
        ReleaseDC(wma->hWndPaint, hDC);
    }
    return TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_14__ {TYPE_1__ rcFrame; int /*<<< orphan*/  dwSampleSize; int /*<<< orphan*/  dwQuality; int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  dwStart; int /*<<< orphan*/  dwRate; int /*<<< orphan*/  dwScale; int /*<<< orphan*/  dwInitialFrames; int /*<<< orphan*/  wLanguage; int /*<<< orphan*/  wPriority; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
struct TYPE_15__ {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; TYPE_11__* inbih; int /*<<< orphan*/  hFile; TYPE_2__ ash_video; } ;
typedef  TYPE_3__ WINE_MCIAVI ;
struct TYPE_16__ {int /*<<< orphan*/  cksize; int /*<<< orphan*/  ckid; } ;
struct TYPE_12__ {int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biClrImportant; int /*<<< orphan*/  biClrUsed; int /*<<< orphan*/  biYPelsPerMeter; int /*<<< orphan*/  biXPelsPerMeter; int /*<<< orphan*/  biSizeImage; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biBitCount; int /*<<< orphan*/  biPlanes; int /*<<< orphan*/  biSize; } ;
typedef  TYPE_4__ MMCKINFO ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 TYPE_11__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_FINDCHUNK ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  ckidSTREAMFORMAT ; 
 int /*<<< orphan*/  mmioAscend (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioDescend (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmioRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL MCIAVI_GetInfoVideo(WINE_MCIAVI* wma, const MMCKINFO* mmckList, MMCKINFO* mmckStream)
{
    MMCKINFO	mmckInfo;

    TRACE("ash.fccType='%c%c%c%c'\n", 		LOBYTE(LOWORD(wma->ash_video.fccType)),
	                                        HIBYTE(LOWORD(wma->ash_video.fccType)),
	                                        LOBYTE(HIWORD(wma->ash_video.fccType)),
	                                        HIBYTE(HIWORD(wma->ash_video.fccType)));
    TRACE("ash.fccHandler='%c%c%c%c'\n",	LOBYTE(LOWORD(wma->ash_video.fccHandler)),
	                                        HIBYTE(LOWORD(wma->ash_video.fccHandler)),
	                                        LOBYTE(HIWORD(wma->ash_video.fccHandler)),
	                                        HIBYTE(HIWORD(wma->ash_video.fccHandler)));
    TRACE("ash.dwFlags=%d\n", 			wma->ash_video.dwFlags);
    TRACE("ash.wPriority=%d\n", 		wma->ash_video.wPriority);
    TRACE("ash.wLanguage=%d\n", 		wma->ash_video.wLanguage);
    TRACE("ash.dwInitialFrames=%d\n", 		wma->ash_video.dwInitialFrames);
    TRACE("ash.dwScale=%d\n", 			wma->ash_video.dwScale);
    TRACE("ash.dwRate=%d\n", 			wma->ash_video.dwRate);
    TRACE("ash.dwStart=%d\n", 			wma->ash_video.dwStart);
    TRACE("ash.dwLength=%d\n", 		wma->ash_video.dwLength);
    TRACE("ash.dwSuggestedBufferSize=%d\n", 	wma->ash_video.dwSuggestedBufferSize);
    TRACE("ash.dwQuality=%d\n", 		wma->ash_video.dwQuality);
    TRACE("ash.dwSampleSize=%d\n", 		wma->ash_video.dwSampleSize);
    TRACE("ash.rcFrame=(%d,%d,%d,%d)\n", 	wma->ash_video.rcFrame.top, wma->ash_video.rcFrame.left,
	  wma->ash_video.rcFrame.bottom, wma->ash_video.rcFrame.right);

    /* rewind to the start of the stream */
    mmioAscend(wma->hFile, mmckStream, 0);

    mmckInfo.ckid = ckidSTREAMFORMAT;
    if (mmioDescend(wma->hFile, &mmckInfo, mmckList, MMIO_FINDCHUNK) != 0) {
       WARN("Can't find 'strf' chunk\n");
	return FALSE;
    }

    wma->inbih = HeapAlloc(GetProcessHeap(), 0, mmckInfo.cksize);
    if (!wma->inbih) {
	WARN("Can't alloc input BIH\n");
	return FALSE;
    }

    mmioRead(wma->hFile, (LPSTR)wma->inbih, mmckInfo.cksize);

    TRACE("bih.biSize=%d\n", 		wma->inbih->biSize);
    TRACE("bih.biWidth=%d\n", 		wma->inbih->biWidth);
    TRACE("bih.biHeight=%d\n", 	wma->inbih->biHeight);
    TRACE("bih.biPlanes=%d\n", 		wma->inbih->biPlanes);
    TRACE("bih.biBitCount=%d\n", 	wma->inbih->biBitCount);
    TRACE("bih.biCompression=%x\n", 	wma->inbih->biCompression);
    TRACE("bih.biSizeImage=%d\n", 	wma->inbih->biSizeImage);
    TRACE("bih.biXPelsPerMeter=%d\n", 	wma->inbih->biXPelsPerMeter);
    TRACE("bih.biYPelsPerMeter=%d\n", 	wma->inbih->biYPelsPerMeter);
    TRACE("bih.biClrUsed=%d\n", 	wma->inbih->biClrUsed);
    TRACE("bih.biClrImportant=%d\n", 	wma->inbih->biClrImportant);

    SetRect(&wma->source, 0, 0, wma->inbih->biWidth, wma->inbih->biHeight);
    wma->dest = wma->source;

    return TRUE;
}
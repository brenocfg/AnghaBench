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
struct TYPE_8__ {int biSizeImage; } ;
struct TYPE_6__ {scalar_t__ dwStart; int dwQuality; } ;
struct TYPE_7__ {scalar_t__ lKeyFrameEvery; scalar_t__ lCurrent; scalar_t__ lLastKey; int dwBytesPerFrame; int dwUnusedBytes; int dwICMFlags; int dwLastQuality; int /*<<< orphan*/ * lpPrev; int /*<<< orphan*/ * lpbiPrev; int /*<<< orphan*/  lpCur; TYPE_3__* lpbiCur; int /*<<< orphan*/  hic; TYPE_1__ sInfo; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPBITMAPINFOHEADER ;
typedef  TYPE_2__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_COMPRESSOR ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int AVIIF_KEYFRAME ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int ICCOMPRESS_KEYFRAME ; 
 int ICCompress (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,scalar_t__,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICDecompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ICERR_NEWPALETTE ; 
 int ICERR_OK ; 
 int ICQUALITY_LOW ; 
 int MAX_FRAMESIZE ; 
 int MAX_FRAMESIZE_DIFF ; 
 int TRUE ; 
 int VIDCF_CRUNCH ; 
 int VIDCF_FASTTEMPORALC ; 
 int VIDCF_QUALITY ; 

__attribute__((used)) static HRESULT AVIFILE_EncodeFrame(IAVIStreamImpl *This,
				   LPBITMAPINFOHEADER lpbi, LPVOID lpBits)
{
  DWORD dwMinQual, dwMaxQual, dwCurQual;
  DWORD dwRequest;
  DWORD icmFlags = 0;
  DWORD idxFlags = 0;
  BOOL  bDecreasedQual = FALSE;
  BOOL  doSizeCheck;
  BOOL  noPrev;

  /* make lKeyFrameEvery and at start a keyframe */
  if ((This->lKeyFrameEvery != 0 &&
       (This->lCurrent - This->lLastKey) >= This->lKeyFrameEvery) ||
      This->lCurrent == This->sInfo.dwStart) {
    idxFlags = AVIIF_KEYFRAME;
    icmFlags = ICCOMPRESS_KEYFRAME;
  }

  if (This->lKeyFrameEvery != 0) {
    if (This->lCurrent == This->sInfo.dwStart) {
      if (idxFlags & AVIIF_KEYFRAME) {
	/* allow keyframes to consume all unused bytes */
	dwRequest = This->dwBytesPerFrame + This->dwUnusedBytes;
	This->dwUnusedBytes = 0;
      } else {
	/* for non-keyframes only allow some of the unused bytes to be consumed */
	DWORD tmp1 = 0;
	DWORD tmp2;

	if (This->dwBytesPerFrame >= This->dwUnusedBytes)
	  tmp1 = This->dwBytesPerFrame / This->lKeyFrameEvery;
	tmp2 = (This->dwUnusedBytes + tmp1) / This->lKeyFrameEvery;

	dwRequest = This->dwBytesPerFrame - tmp1 + tmp2;
	This->dwUnusedBytes -= tmp2;
      }
    } else
      dwRequest = MAX_FRAMESIZE;
  } else {
    /* only one keyframe at start desired */
    if (This->lCurrent == This->sInfo.dwStart) {
      dwRequest = This->dwBytesPerFrame + This->dwUnusedBytes;
      This->dwUnusedBytes = 0;
    } else
      dwRequest = MAX_FRAMESIZE;
  }

  /* must we check for frame size to gain the requested
   * data rate or can we trust the codec? */
  doSizeCheck = (dwRequest != 0 && ((This->dwICMFlags & (VIDCF_CRUNCH|VIDCF_QUALITY)) == 0));

  dwMaxQual = dwCurQual = This->sInfo.dwQuality;
  dwMinQual = ICQUALITY_LOW;

  noPrev = TRUE;
  if ((icmFlags & ICCOMPRESS_KEYFRAME) == 0 && 
      (This->dwICMFlags & VIDCF_FASTTEMPORALC) == 0)
    noPrev = FALSE;

  do {
    DWORD   idxCkid = 0;
    DWORD   res;

    res = ICCompress(This->hic,icmFlags,This->lpbiCur,This->lpCur,lpbi,lpBits,
		     &idxCkid, &idxFlags, This->lCurrent, dwRequest, dwCurQual,
		     noPrev ? NULL:This->lpbiPrev, noPrev ? NULL:This->lpPrev);
    if (res == ICERR_NEWPALETTE) {
      FIXME(": codec has changed palette -- unhandled!\n");
    } else if (res != ICERR_OK)
      return AVIERR_COMPRESSOR;

    /* need to check for framesize */
    if (! doSizeCheck)
      break;

    if (dwRequest >= This->lpbiCur->biSizeImage) {
      /* frame is smaller -- try to maximize quality */
      if (dwMaxQual - dwCurQual > 10) {
	DWORD tmp = dwRequest / 8;

	if (tmp < MAX_FRAMESIZE_DIFF)
	  tmp = MAX_FRAMESIZE_DIFF;

	if (tmp < dwRequest - This->lpbiCur->biSizeImage && bDecreasedQual) {
	  tmp = dwCurQual;
	  dwCurQual = (dwMinQual + dwMaxQual) / 2;
	  dwMinQual = tmp;
	  continue;
	}
      } else
	break;
    } else if (dwMaxQual - dwMinQual <= 1) {
      break;
    } else {
      dwMaxQual = dwCurQual;

      if (bDecreasedQual || dwCurQual == This->dwLastQuality)
	dwCurQual = (dwMinQual + dwMaxQual) / 2;
      else
	FIXME(": no new quality computed min=%u cur=%u max=%u last=%u\n",
	      dwMinQual, dwCurQual, dwMaxQual, This->dwLastQuality);

      bDecreasedQual = TRUE;
    }
  } while (TRUE);

  /* remember some values */
  This->dwLastQuality = dwCurQual;
  This->dwUnusedBytes = dwRequest - This->lpbiCur->biSizeImage;
  if (icmFlags & ICCOMPRESS_KEYFRAME)
    This->lLastKey = This->lCurrent;

  /* Does we manage previous frame? */
  if (This->lpPrev != NULL && This->lKeyFrameEvery != 1)
    ICDecompress(This->hic, 0, This->lpbiCur, This->lpCur,
		 This->lpbiPrev, This->lpPrev);

  return AVIERR_OK;
}
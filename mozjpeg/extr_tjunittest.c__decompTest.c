#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num; int denom; } ;
typedef  TYPE_1__ tjscalingfactor ;
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJSCALED (int,TYPE_1__) ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwtj () ; 
 int /*<<< orphan*/  _tj (int /*<<< orphan*/ ) ; 
 scalar_t__ checkBuf (unsigned char*,int,int,int,int,TYPE_1__,int) ; 
 scalar_t__ checkBufYUV (unsigned char*,int,int,int,TYPE_1__) ; 
 scalar_t__ doYUV ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pad ; 
 char** pixFormatStr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** subNameLong ; 
 unsigned long tjBufSizeYUV2 (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tjDecodeYUV (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int,unsigned char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tjDecompress2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tjDecompressHeader2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,int*,int*,int*) ; 
 int /*<<< orphan*/  tjDecompressToYUV2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tjDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tjInitDecompress () ; 
 int* tjPixelSize ; 

void _decompTest(tjhandle handle, unsigned char *jpegBuf,
                 unsigned long jpegSize, int w, int h, int pf, char *basename,
                 int subsamp, int flags, tjscalingfactor sf)
{
  unsigned char *dstBuf = NULL, *yuvBuf = NULL;
  int _hdrw = 0, _hdrh = 0, _hdrsubsamp = -1;
  int scaledWidth = TJSCALED(w, sf);
  int scaledHeight = TJSCALED(h, sf);
  unsigned long dstSize = 0;

  _tj(tjDecompressHeader2(handle, jpegBuf, jpegSize, &_hdrw, &_hdrh,
                          &_hdrsubsamp));
  if (_hdrw != w || _hdrh != h || _hdrsubsamp != subsamp)
    _throw("Incorrect JPEG header");

  dstSize = scaledWidth * scaledHeight * tjPixelSize[pf];
  if ((dstBuf = (unsigned char *)malloc(dstSize)) == NULL)
    _throw("Memory allocation failure");
  memset(dstBuf, 0, dstSize);

  if (doYUV) {
    unsigned long yuvSize = tjBufSizeYUV2(scaledWidth, pad, scaledHeight,
                                          subsamp);
    tjhandle handle2 = tjInitDecompress();

    if (!handle2) _throwtj();

    if ((yuvBuf = (unsigned char *)malloc(yuvSize)) == NULL)
      _throw("Memory allocation failure");
    memset(yuvBuf, 0, yuvSize);

    printf("JPEG -> YUV %s ", subNameLong[subsamp]);
    if (sf.num != 1 || sf.denom != 1)
      printf("%d/%d ... ", sf.num, sf.denom);
    else printf("... ");
    _tj(tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, scaledWidth, pad,
                           scaledHeight, flags));
    if (checkBufYUV(yuvBuf, scaledWidth, scaledHeight, subsamp, sf))
      printf("Passed.\n");
    else printf("FAILED!\n");

    printf("YUV %s -> %s %s ... ", subNameLong[subsamp], pixFormatStr[pf],
           (flags & TJFLAG_BOTTOMUP) ? "Bottom-Up" : "Top-Down ");
    _tj(tjDecodeYUV(handle2, yuvBuf, pad, subsamp, dstBuf, scaledWidth, 0,
                    scaledHeight, pf, flags));
    tjDestroy(handle2);
  } else {
    printf("JPEG -> %s %s ", pixFormatStr[pf],
           (flags & TJFLAG_BOTTOMUP) ? "Bottom-Up" : "Top-Down ");
    if (sf.num != 1 || sf.denom != 1)
      printf("%d/%d ... ", sf.num, sf.denom);
    else printf("... ");
    _tj(tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, scaledWidth, 0,
                      scaledHeight, pf, flags));
  }

  if (checkBuf(dstBuf, scaledWidth, scaledHeight, pf, subsamp, sf, flags))
    printf("Passed.");
  else printf("FAILED!");
  printf("\n");

bailout:
  if (yuvBuf) free(yuvBuf);
  if (dstBuf) free(dstBuf);
}
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
struct TYPE_3__ {int member_0; int member_1; } ;
typedef  TYPE_1__ tjscalingfactor ;
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJFLAG_NOREALLOC ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwtj () ; 
 int /*<<< orphan*/  _tj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc ; 
 scalar_t__ checkBufYUV (unsigned char*,int,int,int,TYPE_1__) ; 
 scalar_t__ doYUV ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  initBuf (unsigned char*,int,int,int,int) ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pad ; 
 char** pixFormatStr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*,char const*,char*,int) ; 
 char** subName ; 
 char** subNameLong ; 
 unsigned long tjBufSizeYUV2 (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tjCompress2 (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int,int,unsigned char**,unsigned long*,int,int,int) ; 
 int /*<<< orphan*/  tjCompressFromYUV (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int,int,unsigned char**,unsigned long*,int,int) ; 
 int /*<<< orphan*/  tjDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tjEncodeYUV3 (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int,int,unsigned char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tjInitCompress () ; 
 int* tjPixelSize ; 
 int /*<<< orphan*/  writeJPEG (unsigned char*,unsigned long,char*) ; 

void compTest(tjhandle handle, unsigned char **dstBuf, unsigned long *dstSize,
              int w, int h, int pf, char *basename, int subsamp, int jpegQual,
              int flags)
{
  char tempStr[1024];
  unsigned char *srcBuf = NULL, *yuvBuf = NULL;
  const char *pfStr = pixFormatStr[pf];
  const char *buStrLong =
    (flags & TJFLAG_BOTTOMUP) ? "Bottom-Up" : "Top-Down ";
  const char *buStr = (flags & TJFLAG_BOTTOMUP) ? "BU" : "TD";

  if ((srcBuf = (unsigned char *)malloc(w * h * tjPixelSize[pf])) == NULL)
    _throw("Memory allocation failure");
  initBuf(srcBuf, w, h, pf, flags);

  if (*dstBuf && *dstSize > 0) memset(*dstBuf, 0, *dstSize);

  if (!alloc) flags |= TJFLAG_NOREALLOC;
  if (doYUV) {
    unsigned long yuvSize = tjBufSizeYUV2(w, pad, h, subsamp);
    tjscalingfactor sf = { 1, 1 };
    tjhandle handle2 = tjInitCompress();

    if (!handle2) _throwtj();

    if ((yuvBuf = (unsigned char *)malloc(yuvSize)) == NULL)
      _throw("Memory allocation failure");
    memset(yuvBuf, 0, yuvSize);

    printf("%s %s -> YUV %s ... ", pfStr, buStrLong, subNameLong[subsamp]);
    _tj(tjEncodeYUV3(handle2, srcBuf, w, 0, h, pf, yuvBuf, pad, subsamp,
                     flags));
    tjDestroy(handle2);
    if (checkBufYUV(yuvBuf, w, h, subsamp, sf)) printf("Passed.\n");
    else printf("FAILED!\n");

    printf("YUV %s %s -> JPEG Q%d ... ", subNameLong[subsamp], buStrLong,
           jpegQual);
    _tj(tjCompressFromYUV(handle, yuvBuf, w, pad, h, subsamp, dstBuf, dstSize,
                          jpegQual, flags));
  } else {
    printf("%s %s -> %s Q%d ... ", pfStr, buStrLong, subNameLong[subsamp],
           jpegQual);
    _tj(tjCompress2(handle, srcBuf, w, 0, h, pf, dstBuf, dstSize, subsamp,
                    jpegQual, flags));
  }

  snprintf(tempStr, 1024, "%s_enc_%s_%s_%s_Q%d.jpg", basename, pfStr, buStr,
           subName[subsamp], jpegQual);
  writeJPEG(*dstBuf, *dstSize, tempStr);
  printf("Done.\n  Result in %s\n", tempStr);

bailout:
  if (yuvBuf) free(yuvBuf);
  if (srcBuf) free(srcBuf);
}
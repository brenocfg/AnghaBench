#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJFLAG_NOREALLOC ; 
 int TJ_YUV ; 
 int /*<<< orphan*/  getPixelFormat (int,int) ; 
 unsigned long tjBufSizeYUV (int,int,int) ; 
 int tjCompress2 (int /*<<< orphan*/ ,unsigned char*,int,int,int,int /*<<< orphan*/ ,unsigned char**,unsigned long*,int,int,int) ; 
 int tjEncodeYUV2 (int /*<<< orphan*/ ,unsigned char*,int,int,int,int /*<<< orphan*/ ,unsigned char*,int,int) ; 

int tjCompress(tjhandle handle, unsigned char *srcBuf, int width,
                         int pitch, int height, int pixelSize,
                         unsigned char *jpegBuf, unsigned long *jpegSize,
                         int jpegSubsamp, int jpegQual, int flags)
{
  int retval = 0;
  unsigned long size;

  if (flags & TJ_YUV) {
		size=tjBufSizeYUV(width, height, jpegSubsamp);
		retval=tjEncodeYUV2(handle, srcBuf, width, pitch, height,
                          getPixelFormat(pixelSize, flags), jpegBuf,
                          jpegSubsamp, flags);
  } else {
		retval=tjCompress2(handle, srcBuf, width, pitch, height,
                         getPixelFormat(pixelSize, flags), &jpegBuf, &size,
                         jpegSubsamp, jpegQual, flags | TJFLAG_NOREALLOC);
	}
	*jpegSize=size;
	return retval;
}
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
 int TJ_YUV ; 
 int /*<<< orphan*/  getPixelFormat (int,int) ; 
 int tjDecompress2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int tjDecompressToYUV (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int) ; 

int tjDecompress(tjhandle handle, unsigned char *jpegBuf,
                           unsigned long jpegSize, unsigned char *dstBuf,
                           int width, int pitch, int height, int pixelSize,
                           int flags)
{
	if(flags&TJ_YUV)
		return tjDecompressToYUV(handle, jpegBuf, jpegSize, dstBuf, flags);
	else
		return tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, pitch,
			height, getPixelFormat(pixelSize, flags), flags);
}
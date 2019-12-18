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
 int /*<<< orphan*/  getPixelFormat (int,int) ; 
 int tjEncodeYUV2 (int /*<<< orphan*/ ,unsigned char*,int,int,int,int /*<<< orphan*/ ,unsigned char*,int,int) ; 

int tjEncodeYUV(tjhandle handle, unsigned char *srcBuf, int width,
                          int pitch, int height, int pixelSize,
                          unsigned char *dstBuf, int subsamp, int flags)
{
	return tjEncodeYUV2(handle, srcBuf, width, pitch, height,
                      getPixelFormat(pixelSize, flags), dstBuf, subsamp,
                      flags);
}
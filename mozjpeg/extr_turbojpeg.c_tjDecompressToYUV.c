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
 int tjDecompressToYUV2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int tjDecompressToYUV(tjhandle handle, unsigned char *jpegBuf,
                                unsigned long jpegSize, unsigned char *dstBuf,
	int flags)
{
	return tjDecompressToYUV2(handle, jpegBuf, jpegSize, dstBuf, 0, 4, 0, flags);
}
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
 int tjDecompressHeader3 (int /*<<< orphan*/ ,unsigned char*,unsigned long,int*,int*,int*,int*) ; 

int tjDecompressHeader2(tjhandle handle, unsigned char *jpegBuf,
                                  unsigned long jpegSize, int *width,
                                  int *height, int *jpegSubsamp)
{
	int jpegColorspace;

	return tjDecompressHeader3(handle, jpegBuf, jpegSize, width, height,
		jpegSubsamp, &jpegColorspace);
}
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

/* Variables and functions */
 int LZ4_compress_destSize_extState (void*,char const*,char*,int*,int) ; 

int LZ4_compress_destSize(
	const char *src,
	char *dst,
	int *srcSizePtr,
	int targetDstSize,
	void *wrkmem)
{
	return LZ4_compress_destSize_extState(wrkmem, src, dst, srcSizePtr,
		targetDstSize);
}
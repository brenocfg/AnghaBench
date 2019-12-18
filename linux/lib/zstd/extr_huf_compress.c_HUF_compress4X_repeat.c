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
typedef  int /*<<< orphan*/  HUF_repeat ;
typedef  int /*<<< orphan*/  HUF_CElt ;

/* Variables and functions */
 size_t HUF_compress_internal (void*,size_t,void const*,size_t,unsigned int,unsigned int,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

size_t HUF_compress4X_repeat(void *dst, size_t dstSize, const void *src, size_t srcSize, unsigned maxSymbolValue, unsigned huffLog, void *workSpace,
			     size_t wkspSize, HUF_CElt *hufTable, HUF_repeat *repeat, int preferRepeat)
{
	return HUF_compress_internal(dst, dstSize, src, srcSize, maxSymbolValue, huffLog, 0 /* 4 streams */, workSpace, wkspSize, hufTable, repeat,
				     preferRepeat);
}
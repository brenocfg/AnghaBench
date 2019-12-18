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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/  const,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_setRleBlock(void* dst, size_t dstCapacity,
                         const void* src, size_t srcSize,
                               size_t regenSize)
{
    if (srcSize != 1) return ERROR(srcSize_wrong);
    if (regenSize > dstCapacity) return ERROR(dstSize_tooSmall);
    memset(dst, *(const BYTE*)src, regenSize);
    return regenSize;
}
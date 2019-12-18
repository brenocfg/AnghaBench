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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int) ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 
 int /*<<< orphan*/  ZSTD_freeCCtxContent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_initCCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t ZSTD_compress(void* dst, size_t dstCapacity,
               const void* src, size_t srcSize,
                     int compressionLevel)
{
    size_t result;
    ZSTD_CCtx ctxBody;
    ZSTD_initCCtx(&ctxBody, ZSTD_defaultCMem);
    result = ZSTD_compressCCtx(&ctxBody, dst, dstCapacity, src, srcSize, compressionLevel);
    ZSTD_freeCCtxContent(&ctxBody);   /* can't free ctxBody itself, as it's on stack; free only heap content */
    return result;
}
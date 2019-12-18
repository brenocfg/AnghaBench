#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dStage; size_t dictSize; int /*<<< orphan*/  const* dict; } ;
typedef  int /*<<< orphan*/  LZ4F_decompressOptions_t ;
typedef  TYPE_1__ LZ4F_dctx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t LZ4F_decompress (TYPE_1__*,void*,size_t*,void const*,size_t*,int /*<<< orphan*/  const*) ; 
 scalar_t__ dstage_init ; 

size_t LZ4F_decompress_usingDict(LZ4F_dctx* dctx,
                       void* dstBuffer, size_t* dstSizePtr,
                       const void* srcBuffer, size_t* srcSizePtr,
                       const void* dict, size_t dictSize,
                       const LZ4F_decompressOptions_t* decompressOptionsPtr)
{
    if (dctx->dStage <= dstage_init) {
        dctx->dict = (const BYTE*)dict;
        dctx->dictSize = dictSize;
    }
    return LZ4F_decompress(dctx, dstBuffer, dstSizePtr,
                           srcBuffer, srcSizePtr,
                           decompressOptionsPtr);
}
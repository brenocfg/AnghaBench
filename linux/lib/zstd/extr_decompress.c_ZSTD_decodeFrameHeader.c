#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dictID; scalar_t__ checksumFlag; } ;
struct TYPE_4__ {scalar_t__ dictID; int /*<<< orphan*/  xxhState; TYPE_2__ fParams; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_getFrameParams (TYPE_2__*,void const*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  dictionary_wrong ; 
 int /*<<< orphan*/  srcSize_wrong ; 
 int /*<<< orphan*/  xxh64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_decodeFrameHeader(ZSTD_DCtx *dctx, const void *src, size_t headerSize)
{
	size_t const result = ZSTD_getFrameParams(&(dctx->fParams), src, headerSize);
	if (ZSTD_isError(result))
		return result; /* invalid header */
	if (result > 0)
		return ERROR(srcSize_wrong); /* headerSize too small */
	if (dctx->fParams.dictID && (dctx->dictID != dctx->fParams.dictID))
		return ERROR(dictionary_wrong);
	if (dctx->fParams.checksumFlag)
		xxh64_reset(&dctx->xxhState, 0);
	return 0;
}
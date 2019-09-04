#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pos; int size; scalar_t__ dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_7__ {scalar_t__ pledgedSrcSize; scalar_t__ inputProcessed; scalar_t__ stage; size_t outBuffContentSize; size_t outBuffFlushedSize; int checksum; size_t outBuff; int /*<<< orphan*/  outBuffSize; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_2__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_BLOCKHEADERSIZE ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressStream_generic (TYPE_2__*,int /*<<< orphan*/ * const,size_t*,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 size_t ZSTD_limitCopy (int /*<<< orphan*/ *,int,size_t,size_t const) ; 
 int /*<<< orphan*/  srcSize_wrong ; 
 scalar_t__ zcss_final ; 
 scalar_t__ zcss_init ; 
 int /*<<< orphan*/  zsf_end ; 

size_t ZSTD_endStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output)
{
	BYTE *const ostart = (BYTE *)(output->dst) + output->pos;
	BYTE *const oend = (BYTE *)(output->dst) + output->size;
	BYTE *op = ostart;

	if ((zcs->pledgedSrcSize) && (zcs->inputProcessed != zcs->pledgedSrcSize))
		return ERROR(srcSize_wrong); /* pledgedSrcSize not respected */

	if (zcs->stage != zcss_final) {
		/* flush whatever remains */
		size_t srcSize = 0;
		size_t sizeWritten = output->size - output->pos;
		size_t const notEnded =
		    ZSTD_compressStream_generic(zcs, ostart, &sizeWritten, &srcSize, &srcSize, zsf_end); /* use a valid src address instead of NULL */
		size_t const remainingToFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize;
		op += sizeWritten;
		if (remainingToFlush) {
			output->pos += sizeWritten;
			return remainingToFlush + ZSTD_BLOCKHEADERSIZE /* final empty block */ + (zcs->checksum * 4);
		}
		/* create epilogue */
		zcs->stage = zcss_final;
		zcs->outBuffContentSize = !notEnded ? 0 : ZSTD_compressEnd(zcs->cctx, zcs->outBuff, zcs->outBuffSize, NULL,
									   0); /* write epilogue, including final empty block, into outBuff */
	}

	/* flush epilogue */
	{
		size_t const toFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize;
		size_t const flushed = ZSTD_limitCopy(op, oend - op, zcs->outBuff + zcs->outBuffFlushedSize, toFlush);
		op += flushed;
		zcs->outBuffFlushedSize += flushed;
		output->pos += op - ostart;
		if (toFlush == flushed)
			zcs->stage = zcss_init; /* end reached */
		return toFlush - flushed;
	}
}
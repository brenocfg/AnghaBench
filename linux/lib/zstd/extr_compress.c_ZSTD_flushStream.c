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
struct TYPE_6__ {size_t size; size_t pos; scalar_t__ dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_7__ {size_t outBuffContentSize; size_t outBuffFlushedSize; } ;
typedef  TYPE_2__ ZSTD_CStream ;

/* Variables and functions */
 size_t ZSTD_compressStream_generic (TYPE_2__*,char*,size_t*,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  zsf_flush ; 

size_t ZSTD_flushStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output)
{
	size_t srcSize = 0;
	size_t sizeWritten = output->size - output->pos;
	size_t const result = ZSTD_compressStream_generic(zcs, (char *)(output->dst) + output->pos, &sizeWritten, &srcSize,
							  &srcSize, /* use a valid src address instead of NULL */
							  zsf_flush);
	output->pos += sizeWritten;
	if (ZSTD_isError(result))
		return result;
	return zcs->outBuffContentSize - zcs->outBuffFlushedSize; /* remaining to flush */
}
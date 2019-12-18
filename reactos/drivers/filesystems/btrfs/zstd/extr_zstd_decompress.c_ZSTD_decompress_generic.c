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
typedef  int /*<<< orphan*/  ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 size_t ZSTD_decompressStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t ZSTD_decompress_generic(ZSTD_DCtx* dctx, ZSTD_outBuffer* output, ZSTD_inBuffer* input)
{
    return ZSTD_decompressStream(dctx, output, input);
}
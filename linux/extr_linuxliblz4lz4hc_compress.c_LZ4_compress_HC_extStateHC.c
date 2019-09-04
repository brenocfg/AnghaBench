#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ state ;
struct TYPE_2__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamHC_t ;
typedef  int /*<<< orphan*/  LZ4HC_CCtx_internal ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int LZ4HC_compress_generic (int /*<<< orphan*/ *,char const*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4HC_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int LZ4_compressBound (int) ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  noLimit ; 

__attribute__((used)) static int LZ4_compress_HC_extStateHC(
	void *state,
	const char *src,
	char *dst,
	int srcSize,
	int maxDstSize,
	int compressionLevel)
{
	LZ4HC_CCtx_internal *ctx = &((LZ4_streamHC_t *)state)->internal_donotuse;

	if (((size_t)(state)&(sizeof(void *) - 1)) != 0) {
		/* Error : state is not aligned
		 * for pointers (32 or 64 bits)
		 */
		return 0;
	}

	LZ4HC_init(ctx, (const BYTE *)src);

	if (maxDstSize < LZ4_compressBound(srcSize))
		return LZ4HC_compress_generic(ctx, src, dst,
			srcSize, maxDstSize, compressionLevel, limitedOutput);
	else
		return LZ4HC_compress_generic(ctx, src, dst,
			srcSize, maxDstSize, compressionLevel, noLimit);
}
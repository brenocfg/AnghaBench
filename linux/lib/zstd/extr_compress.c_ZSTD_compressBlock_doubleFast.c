#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int searchLength; } ;
struct TYPE_7__ {TYPE_1__ cParams; } ;
struct TYPE_8__ {TYPE_2__ params; } ;
typedef  TYPE_3__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_compressBlock_doubleFast_generic (TYPE_3__*,void const*,size_t,int) ; 

__attribute__((used)) static void ZSTD_compressBlock_doubleFast(ZSTD_CCtx *ctx, const void *src, size_t srcSize)
{
	const U32 mls = ctx->params.cParams.searchLength;
	switch (mls) {
	default: /* includes case 3 */
	case 4: ZSTD_compressBlock_doubleFast_generic(ctx, src, srcSize, 4); return;
	case 5: ZSTD_compressBlock_doubleFast_generic(ctx, src, srcSize, 5); return;
	case 6: ZSTD_compressBlock_doubleFast_generic(ctx, src, srcSize, 6); return;
	case 7: ZSTD_compressBlock_doubleFast_generic(ctx, src, srcSize, 7); return;
	}
}
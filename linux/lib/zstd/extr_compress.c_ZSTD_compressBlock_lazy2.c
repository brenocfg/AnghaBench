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
 int /*<<< orphan*/  ZSTD_compressBlock_lazy_generic (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ZSTD_compressBlock_lazy2(ZSTD_CCtx *ctx, const void *src, size_t srcSize) { ZSTD_compressBlock_lazy_generic(ctx, src, srcSize, 0, 2); }
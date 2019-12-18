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
typedef  int /*<<< orphan*/  ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_compResetPolicy_e ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U64 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 size_t ZSTD_compress_insertDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_resetCCtx_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTDcrp_continue ; 
 int /*<<< orphan*/  ZSTDcrp_fullReset ; 

__attribute__((used)) static size_t ZSTD_compressBegin_internal(ZSTD_CCtx *cctx, const void *dict, size_t dictSize, ZSTD_parameters params, U64 pledgedSrcSize)
{
	ZSTD_compResetPolicy_e const crp = dictSize ? ZSTDcrp_fullReset : ZSTDcrp_continue;
	CHECK_F(ZSTD_resetCCtx_advanced(cctx, params, pledgedSrcSize, crp));
	return ZSTD_compress_insertDictionary(cctx, dict, dictSize);
}
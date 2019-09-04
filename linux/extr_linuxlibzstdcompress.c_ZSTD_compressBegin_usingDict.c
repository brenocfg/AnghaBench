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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_compressBegin_internal (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_getParams (int,int /*<<< orphan*/ ,size_t) ; 

size_t ZSTD_compressBegin_usingDict(ZSTD_CCtx *cctx, const void *dict, size_t dictSize, int compressionLevel)
{
	ZSTD_parameters const params = ZSTD_getParams(compressionLevel, 0, dictSize);
	return ZSTD_compressBegin_internal(cctx, dict, dictSize, params, 0);
}
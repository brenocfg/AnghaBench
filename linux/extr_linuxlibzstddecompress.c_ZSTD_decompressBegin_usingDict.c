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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_E (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_decompress_insertDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

size_t ZSTD_decompressBegin_usingDict(ZSTD_DCtx *dctx, const void *dict, size_t dictSize)
{
	CHECK_F(ZSTD_decompressBegin(dctx));
	if (dict && dictSize)
		CHECK_E(ZSTD_decompress_insertDictionary(dctx, dict, dictSize), dictionary_corrupted);
	return 0;
}
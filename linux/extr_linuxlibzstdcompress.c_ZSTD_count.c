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
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ ZSTD_64bits () ; 
 int /*<<< orphan*/  ZSTD_NbCommonBytes (size_t const) ; 
 scalar_t__ ZSTD_read16 (scalar_t__ const*) ; 
 scalar_t__ ZSTD_read32 (scalar_t__ const*) ; 
 size_t ZSTD_readST (scalar_t__ const*) ; 

__attribute__((used)) static size_t ZSTD_count(const BYTE *pIn, const BYTE *pMatch, const BYTE *const pInLimit)
{
	const BYTE *const pStart = pIn;
	const BYTE *const pInLoopLimit = pInLimit - (sizeof(size_t) - 1);

	while (pIn < pInLoopLimit) {
		size_t const diff = ZSTD_readST(pMatch) ^ ZSTD_readST(pIn);
		if (!diff) {
			pIn += sizeof(size_t);
			pMatch += sizeof(size_t);
			continue;
		}
		pIn += ZSTD_NbCommonBytes(diff);
		return (size_t)(pIn - pStart);
	}
	if (ZSTD_64bits())
		if ((pIn < (pInLimit - 3)) && (ZSTD_read32(pMatch) == ZSTD_read32(pIn))) {
			pIn += 4;
			pMatch += 4;
		}
	if ((pIn < (pInLimit - 1)) && (ZSTD_read16(pMatch) == ZSTD_read16(pIn))) {
		pIn += 2;
		pMatch += 2;
	}
	if ((pIn < pInLimit) && (*pMatch == *pIn))
		pIn++;
	return (size_t)(pIn - pStart);
}
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
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ZSTD_BtFindBestMatch_extDict (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const,size_t*,int const,int) ; 

__attribute__((used)) static size_t ZSTD_BtFindBestMatch_selectMLS_extDict(ZSTD_CCtx *zc, /* Index table will be updated */
						     const BYTE *ip, const BYTE *const iLimit, size_t *offsetPtr, const U32 maxNbAttempts,
						     const U32 matchLengthSearch)
{
	switch (matchLengthSearch) {
	default: /* includes case 3 */
	case 4: return ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 4);
	case 5: return ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 5);
	case 7:
	case 6: return ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 6);
	}
}
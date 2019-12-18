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
typedef  int /*<<< orphan*/  ZSTD_match_t ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ZSTD_BtGetAllMatches (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const,int const,int,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static U32 ZSTD_BtGetAllMatches_selectMLS(ZSTD_CCtx *zc, /* Index table will be updated */
					  const BYTE *ip, const BYTE *const iHighLimit, const U32 maxNbAttempts, const U32 matchLengthSearch,
					  ZSTD_match_t *matches, const U32 minMatchLen)
{
	switch (matchLengthSearch) {
	case 3: return ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 3, matches, minMatchLen);
	default:
	case 4: return ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 4, matches, minMatchLen);
	case 5: return ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 5, matches, minMatchLen);
	case 7:
	case 6: return ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 6, matches, minMatchLen);
	}
}
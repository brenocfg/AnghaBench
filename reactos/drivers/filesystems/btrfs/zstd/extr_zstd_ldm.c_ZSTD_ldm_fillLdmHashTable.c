#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hashPower; } ;
typedef  TYPE_1__ ldmState_t ;
struct TYPE_8__ {int minMatchLength; } ;
typedef  TYPE_2__ ldmParams_t ;
typedef  int /*<<< orphan*/  U64 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_ldm_makeEntryAndInsertByTag (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const) ; 
 int /*<<< orphan*/  ZSTD_ldm_updateHash (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static U64 ZSTD_ldm_fillLdmHashTable(ldmState_t* state,
                                     U64 lastHash, const BYTE* lastHashed,
                                     const BYTE* iend, const BYTE* base,
                                     U32 hBits, ldmParams_t const ldmParams)
{
    U64 rollingHash = lastHash;
    const BYTE* cur = lastHashed + 1;

    while (cur < iend) {
        rollingHash = ZSTD_ldm_updateHash(rollingHash, cur[-1],
                                          cur[ldmParams.minMatchLength-1],
                                          state->hashPower);
        ZSTD_ldm_makeEntryAndInsertByTag(state,
                                         rollingHash, hBits,
                                         (U32)(cur - base), ldmParams);
        ++cur;
    }
    return rollingHash;
}
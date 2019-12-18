#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  searchLength; } ;
struct TYPE_6__ {TYPE_2__ cParams; } ;
typedef  TYPE_1__ ZSTD_matchState_t ;
typedef  TYPE_2__ ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_insertAndFindFirstIndex_internal (TYPE_1__*,TYPE_2__ const* const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

U32 ZSTD_insertAndFindFirstIndex(ZSTD_matchState_t* ms, const BYTE* ip) {
    const ZSTD_compressionParameters* const cParams = &ms->cParams;
    return ZSTD_insertAndFindFirstIndex_internal(ms, cParams, ip, ms->cParams.searchLength);
}
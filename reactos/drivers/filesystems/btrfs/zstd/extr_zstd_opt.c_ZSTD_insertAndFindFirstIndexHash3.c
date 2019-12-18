#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;
struct TYPE_5__ {scalar_t__* hashTable3; scalar_t__ hashLog3; scalar_t__ nextToUpdate3; TYPE_1__ window; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ZSTD_hash3Ptr (int /*<<< orphan*/  const* const,scalar_t__ const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static U32 ZSTD_insertAndFindFirstIndexHash3 (ZSTD_matchState_t* ms, const BYTE* const ip)
{
    U32* const hashTable3 = ms->hashTable3;
    U32 const hashLog3 = ms->hashLog3;
    const BYTE* const base = ms->window.base;
    U32 idx = ms->nextToUpdate3;
    U32 const target = ms->nextToUpdate3 = (U32)(ip - base);
    size_t const hash3 = ZSTD_hash3Ptr(ip, hashLog3);
    assert(hashLog3 > 0);

    while(idx < target) {
        hashTable3[ZSTD_hash3Ptr(base+idx, hashLog3)] = idx;
        idx++;
    }

    return hashTable3[hash3];
}
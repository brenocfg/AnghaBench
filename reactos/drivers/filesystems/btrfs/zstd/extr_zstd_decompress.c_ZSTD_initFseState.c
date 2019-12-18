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
struct TYPE_4__ {int /*<<< orphan*/  tableLog; } ;
typedef  TYPE_1__ ZSTD_seqSymbol_header ;
typedef  int /*<<< orphan*/  ZSTD_seqSymbol ;
struct TYPE_5__ {int /*<<< orphan*/  const* table; scalar_t__ state; } ;
typedef  TYPE_2__ ZSTD_fseState ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BIT_DStream_t ;

/* Variables and functions */
 scalar_t__ BIT_readBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_reloadDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ZSTD_initFseState(ZSTD_fseState* DStatePtr, BIT_DStream_t* bitD, const ZSTD_seqSymbol* dt)
{
    const void* ptr = dt;
    const ZSTD_seqSymbol_header* const DTableH = (const ZSTD_seqSymbol_header*)ptr;
    DStatePtr->state = BIT_readBits(bitD, DTableH->tableLog);
    DEBUGLOG(6, "ZSTD_initFseState : val=%u using %u bits",
                (U32)DStatePtr->state, DTableH->tableLog);
    BIT_reloadDStream(bitD);
    DStatePtr->table = dt + 1;
}
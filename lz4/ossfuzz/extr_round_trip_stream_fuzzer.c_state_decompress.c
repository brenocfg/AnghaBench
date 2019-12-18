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
struct TYPE_4__ {char* buf; int pos; int size; } ;
struct TYPE_5__ {TYPE_1__ roundTrip; int /*<<< orphan*/  dstream; } ;
typedef  TYPE_2__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int LZ4_decompress_safe_continue (int /*<<< orphan*/ ,char const*,char*,int,int const) ; 

__attribute__((used)) static void state_decompress(state_t* state, char const* src, int srcSize)
{
    char* dst = state->roundTrip.buf + state->roundTrip.pos;
    int const dstCapacity = state->roundTrip.size - state->roundTrip.pos;
    int const dSize = LZ4_decompress_safe_continue(state->dstream, src, dst,
                                                   srcSize, dstCapacity);
    FUZZ_ASSERT(dSize >= 0);
    state->roundTrip.pos += dSize;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ pos; int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {scalar_t__ pos; int /*<<< orphan*/  buf; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {TYPE_1__ roundTrip; TYPE_2__ data; int /*<<< orphan*/  seed; } ;
typedef  TYPE_3__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,size_t const) ; 
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 size_t FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static size_t state_trimDict(state_t* state)
{
    /* 64 KB is the max dict size, allow slightly beyond that to test trim. */
    uint32_t maxDictSize = MIN(70 * 1024, state->data.size);
    size_t const dictSize = FUZZ_rand32(&state->seed, 0, maxDictSize);
    DEBUGLOG(2, "dictSize = %zu", dictSize);
    FUZZ_ASSERT(state->data.pos == 0);
    FUZZ_ASSERT(state->roundTrip.pos == 0);
    memcpy(state->roundTrip.buf, state->data.buf, dictSize);
    state->data.pos += dictSize;
    state->roundTrip.pos += dictSize;
    return dictSize;
}
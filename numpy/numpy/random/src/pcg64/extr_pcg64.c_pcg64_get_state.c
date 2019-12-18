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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int has_uint32; int /*<<< orphan*/  uinteger; TYPE_1__* pcg_state; } ;
typedef  TYPE_2__ pcg64_state ;
struct TYPE_4__ {int state; int inc; } ;

/* Variables and functions */

extern void pcg64_get_state(pcg64_state *state, uint64_t *state_arr,
                            int *has_uint32, uint32_t *uinteger) {
  /*
   * state_arr contains state.high, state.low, inc.high, inc.low
   *    which are interpreted as the upper 64 bits (high) or lower
   *    64 bits of a uint128_t variable
   *
   */
#ifndef PCG_EMULATED_128BIT_MATH
  state_arr[0] = (uint64_t)(state->pcg_state->state >> 64);
  state_arr[1] = (uint64_t)(state->pcg_state->state & 0xFFFFFFFFFFFFFFFFULL);
  state_arr[2] = (uint64_t)(state->pcg_state->inc >> 64);
  state_arr[3] = (uint64_t)(state->pcg_state->inc & 0xFFFFFFFFFFFFFFFFULL);
#else
  state_arr[0] = (uint64_t)state->pcg_state->state.high;
  state_arr[1] = (uint64_t)state->pcg_state->state.low;
  state_arr[2] = (uint64_t)state->pcg_state->inc.high;
  state_arr[3] = (uint64_t)state->pcg_state->inc.low;
#endif
  has_uint32[0] = state->has_uint32;
  uinteger[0] = state->uinteger;
}
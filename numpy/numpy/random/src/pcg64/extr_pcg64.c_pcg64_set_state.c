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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int has_uint32; int /*<<< orphan*/  uinteger; TYPE_1__* pcg_state; } ;
typedef  TYPE_2__ pcg64_state ;
typedef  int pcg128_t ;
struct TYPE_4__ {int state; int inc; } ;

/* Variables and functions */

extern void pcg64_set_state(pcg64_state *state, uint64_t *state_arr,
                            int has_uint32, uint32_t uinteger) {
  /*
   * state_arr contains state.high, state.low, inc.high, inc.low
   *    which are interpreted as the upper 64 bits (high) or lower
   *    64 bits of a uint128_t variable
   *
   */
#ifndef PCG_EMULATED_128BIT_MATH
  state->pcg_state->state = (((pcg128_t)state_arr[0]) << 64) | state_arr[1];
  state->pcg_state->inc = (((pcg128_t)state_arr[2]) << 64) | state_arr[3];
#else
  state->pcg_state->state.high = state_arr[0];
  state->pcg_state->state.low = state_arr[1];
  state->pcg_state->inc.high = state_arr[2];
  state->pcg_state->inc.low = state_arr[3];
#endif
  state->has_uint32 = has_uint32;
  state->uinteger = uinteger;
}
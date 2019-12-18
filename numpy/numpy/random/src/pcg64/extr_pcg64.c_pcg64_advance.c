#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  pcg_state; } ;
typedef  TYPE_1__ pcg64_state ;
typedef  int pcg128_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcg64_advance_r (int /*<<< orphan*/ ,int) ; 

extern void pcg64_advance(pcg64_state *state, uint64_t *step) {
  pcg128_t delta;
#ifndef PCG_EMULATED_128BIT_MATH
  delta = (((pcg128_t)step[0]) << 64) | step[1];
#else
  delta.high = step[0];
  delta.low = step[1];
#endif
  pcg64_advance_r(state->pcg_state, delta);
}
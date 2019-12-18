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
 int /*<<< orphan*/  pcg64_srandom_r (int /*<<< orphan*/ ,int,int) ; 

extern void pcg64_set_seed(pcg64_state *state, uint64_t *seed, uint64_t *inc) {
  pcg128_t s, i;
#ifndef PCG_EMULATED_128BIT_MATH
  s = (((pcg128_t)seed[0]) << 64) | seed[1];
  i = (((pcg128_t)inc[0]) << 64) | inc[1];
#else
  s.high = seed[0];
  s.low = seed[1];
  i.high = inc[0];
  i.low = inc[1];
#endif
  pcg64_srandom_r(state->pcg_state, s, i);
}
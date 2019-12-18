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
typedef  void* uint64_t ;
struct TYPE_3__ {int* s; } ;
typedef  TYPE_1__ sfc64_state ;

/* Variables and functions */
 int /*<<< orphan*/  sfc64_next (int*) ; 

extern void sfc64_set_seed(sfc64_state *state, uint64_t *seed) {
  /* Conservatively stick with the original formula. With SeedSequence, it
   * might be fine to just set the state with 4 uint64s and be done.
   */
  int i;

  state->s[0] = seed[0];
  state->s[1] = seed[1];
  state->s[2] = seed[2];
  state->s[3] = 1;

  for (i=0; i<12; i++) {
    (void)sfc64_next(state->s);
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ pos; int* key; } ;
typedef  TYPE_1__ mt19937_state ;

/* Variables and functions */
 scalar_t__ RK_STATE_LEN ; 
 int /*<<< orphan*/  mt19937_gen (TYPE_1__*) ; 

__attribute__((used)) static inline uint32_t mt19937_next(mt19937_state *state) {
  uint32_t y;

  if (state->pos == RK_STATE_LEN) {
    // Move to function to help inlining
    mt19937_gen(state);
  }
  y = state->key[state->pos++];

  /* Tempering */
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680UL;
  y ^= (y << 15) & 0xefc60000UL;
  y ^= (y >> 18);

  return y;
}
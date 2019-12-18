#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rk_state ;

/* Variables and functions */
 unsigned long rk_random (int /*<<< orphan*/ *) ; 
 unsigned long rk_ulong (int /*<<< orphan*/ *) ; 

unsigned long rk_interval(unsigned long max, rk_state *state) {
  unsigned long mask = max, value;

  if (max == 0) {
    return 0;
  }
  /* Smallest bit mask >= max */
  mask |= mask >> 1;
  mask |= mask >> 2;
  mask |= mask >> 4;
  mask |= mask >> 8;
  mask |= mask >> 16;
#if ULONG_MAX > 0xffffffffUL
  mask |= mask >> 32;
#endif

  /* Search a random value in [0..mask] <= max */
#if ULONG_MAX > 0xffffffffUL
  if (max <= 0xffffffffUL) {
    while ((value = (rk_random(state) & mask)) > max)
      ;
  } else {
    while ((value = (rk_ulong(state) & mask)) > max)
      ;
  }
#else
  while ((value = (rk_ulong(state) & mask)) > max)
    ;
#endif
  return value;
}
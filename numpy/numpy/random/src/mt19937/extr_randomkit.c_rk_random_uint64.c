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
typedef  int npy_uint64 ;
typedef  size_t npy_intp ;

/* Variables and functions */
 int rk_uint32 (int /*<<< orphan*/ *) ; 
 int rk_uint64 (int /*<<< orphan*/ *) ; 

void rk_random_uint64(npy_uint64 off, npy_uint64 rng, npy_intp cnt,
                      npy_uint64 *out, rk_state *state) {
  npy_uint64 val, mask = rng;
  npy_intp i;

  if (rng == 0) {
    for (i = 0; i < cnt; i++) {
      out[i] = off;
    }
    return;
  }

  /* Smallest bit mask >= max */
  mask |= mask >> 1;
  mask |= mask >> 2;
  mask |= mask >> 4;
  mask |= mask >> 8;
  mask |= mask >> 16;
  mask |= mask >> 32;

  for (i = 0; i < cnt; i++) {
    if (rng <= 0xffffffffUL) {
      while ((val = (rk_uint32(state) & mask)) > rng)
        ;
    } else {
      while ((val = (rk_uint64(state) & mask)) > rng)
        ;
    }
    out[i] = off + val;
  }
}
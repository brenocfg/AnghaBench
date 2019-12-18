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
typedef  int uint32_t ;
struct TYPE_3__ {int* seed; } ;
typedef  TYPE_1__ rand_state ;

/* Variables and functions */

__attribute__((used)) static uint32_t
rand_uint32(rand_state *state)
{
  uint32_t *seed = state->seed;
  uint32_t x = seed[0];
  uint32_t y = seed[1];
  uint32_t z = seed[2];
  uint32_t t;

  t = (x ^ (x << 3)) ^ (y ^ (y >> 19)) ^ (z ^ (z << 6));
  x = y; y = z; z = t;
  seed[0] = x;
  seed[1] = y;
  seed[2] = z;

  return z;
}
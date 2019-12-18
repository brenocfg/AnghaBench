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

void rk_fill(void *buffer, size_t size, rk_state *state) {
  unsigned long r;
  unsigned char *buf = buffer;

  for (; size >= 4; size -= 4) {
    r = rk_random(state);
    *(buf++) = r & 0xFF;
    *(buf++) = (r >> 8) & 0xFF;
    *(buf++) = (r >> 16) & 0xFF;
    *(buf++) = (r >> 24) & 0xFF;
  }

  if (!size) {
    return;
  }
  r = rk_random(state);
  for (; size; r >>= 8, size--) {
    *(buf++) = (unsigned char)(r & 0xFF);
  }
}
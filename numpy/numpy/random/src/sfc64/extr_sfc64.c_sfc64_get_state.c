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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int has_uint32; int /*<<< orphan*/  uinteger; int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ sfc64_state ;

/* Variables and functions */

extern void sfc64_get_state(sfc64_state *state, uint64_t *state_arr, int *has_uint32,
                            uint32_t *uinteger) {
  int i;

  for (i=0; i<4; i++) {
    state_arr[i] = state->s[i];
  }
  has_uint32[0] = state->has_uint32;
  uinteger[0] = state->uinteger;
}
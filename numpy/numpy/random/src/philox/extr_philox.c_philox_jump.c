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
struct TYPE_5__ {TYPE_1__* ctr; } ;
typedef  TYPE_2__ philox_state ;
struct TYPE_4__ {scalar_t__* v; } ;

/* Variables and functions */

extern void philox_jump(philox_state *state) {
  /* Advances state as-if 2^128 draws were made */
  state->ctr->v[2]++;
  if (state->ctr->v[2] == 0) {
    state->ctr->v[3]++;
  }
}
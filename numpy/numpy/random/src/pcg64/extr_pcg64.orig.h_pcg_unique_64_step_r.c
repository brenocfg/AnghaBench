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
typedef  int uint64_t ;
struct pcg_state_64 {int state; } ;

/* Variables and functions */
 int PCG_DEFAULT_MULTIPLIER_64 ; 

inline void pcg_unique_64_step_r(struct pcg_state_64 *rng) {
  rng->state =
      rng->state * PCG_DEFAULT_MULTIPLIER_64 + (uint64_t)(((intptr_t)rng) | 1u);
}
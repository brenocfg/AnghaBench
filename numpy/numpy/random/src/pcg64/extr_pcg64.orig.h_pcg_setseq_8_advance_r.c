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
typedef  int /*<<< orphan*/  uint8_t ;
struct pcg_state_setseq_8 {int /*<<< orphan*/  inc; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCG_DEFAULT_MULTIPLIER_8 ; 
 int /*<<< orphan*/  pcg_advance_lcg_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void pcg_setseq_8_advance_r(struct pcg_state_setseq_8 *rng,
                                   uint8_t delta) {
  rng->state =
      pcg_advance_lcg_8(rng->state, delta, PCG_DEFAULT_MULTIPLIER_8, rng->inc);
}
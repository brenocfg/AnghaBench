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
typedef  scalar_t__ uint16_t ;
struct pcg_state_16 {unsigned int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_oneseq_16_step_r (struct pcg_state_16*) ; 

inline void pcg_oneseq_16_srandom_r(struct pcg_state_16 *rng,
                                    uint16_t initstate) {
  rng->state = 0U;
  pcg_oneseq_16_step_r(rng);
  rng->state += initstate;
  pcg_oneseq_16_step_r(rng);
}
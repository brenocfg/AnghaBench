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
typedef  int /*<<< orphan*/  uint16_t ;
struct pcg_state_setseq_16 {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_output_rxs_m_xs_16_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcg_setseq_16_step_r (struct pcg_state_setseq_16*) ; 

inline uint16_t
pcg_setseq_16_rxs_m_xs_16_random_r(struct pcg_state_setseq_16 *rng) {
  uint16_t oldstate = rng->state;
  pcg_setseq_16_step_r(rng);
  return pcg_output_rxs_m_xs_16_16(oldstate);
}
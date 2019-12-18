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
typedef  int /*<<< orphan*/  uint64_t ;
struct pcg_state_setseq_64 {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_output_rxs_m_xs_64_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcg_setseq_64_step_r (struct pcg_state_setseq_64*) ; 

inline uint64_t
pcg_setseq_64_rxs_m_xs_64_random_r(struct pcg_state_setseq_64 *rng) {
  uint64_t oldstate = rng->state;
  pcg_setseq_64_step_r(rng);
  return pcg_output_rxs_m_xs_64_64(oldstate);
}
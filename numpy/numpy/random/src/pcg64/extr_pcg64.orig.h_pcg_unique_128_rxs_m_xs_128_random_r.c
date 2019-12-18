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
struct pcg_state_128 {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  pcg128_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_output_rxs_m_xs_128_128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcg_unique_128_step_r (struct pcg_state_128*) ; 

inline pcg128_t
pcg_unique_128_rxs_m_xs_128_random_r(struct pcg_state_128 *rng) {
  pcg_unique_128_step_r(rng);
  return pcg_output_rxs_m_xs_128_128(rng->state);
}
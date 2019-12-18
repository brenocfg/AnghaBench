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
typedef  int uint8_t ;
struct pcg_state_setseq_8 {int dummy; } ;

/* Variables and functions */
 int pcg_setseq_8_rxs_m_xs_8_random_r (struct pcg_state_setseq_8*) ; 

inline uint8_t
pcg_setseq_8_rxs_m_xs_8_boundedrand_r(struct pcg_state_setseq_8 *rng,
                                      uint8_t bound) {
  uint8_t threshold = ((uint8_t)(-bound)) % bound;
  for (;;) {
    uint8_t r = pcg_setseq_8_rxs_m_xs_8_random_r(rng);
    if (r >= threshold)
      return r % bound;
  }
}
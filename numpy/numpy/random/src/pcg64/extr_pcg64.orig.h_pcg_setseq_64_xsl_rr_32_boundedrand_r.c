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
typedef  int uint32_t ;
struct pcg_state_setseq_64 {int dummy; } ;

/* Variables and functions */
 int pcg_setseq_64_xsl_rr_32_random_r (struct pcg_state_setseq_64*) ; 

inline uint32_t
pcg_setseq_64_xsl_rr_32_boundedrand_r(struct pcg_state_setseq_64 *rng,
                                      uint32_t bound) {
  uint32_t threshold = -bound % bound;
  for (;;) {
    uint32_t r = pcg_setseq_64_xsl_rr_32_random_r(rng);
    if (r >= threshold)
      return r % bound;
  }
}
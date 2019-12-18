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
struct pcg_state_128 {int dummy; } ;

/* Variables and functions */
 int pcg_unique_128_xsh_rs_64_random_r (struct pcg_state_128*) ; 

inline uint64_t
pcg_unique_128_xsh_rs_64_boundedrand_r(struct pcg_state_128 *rng,
                                       uint64_t bound) {
  uint64_t threshold = -bound % bound;
  for (;;) {
    uint64_t r = pcg_unique_128_xsh_rs_64_random_r(rng);
    if (r >= threshold)
      return r % bound;
  }
}
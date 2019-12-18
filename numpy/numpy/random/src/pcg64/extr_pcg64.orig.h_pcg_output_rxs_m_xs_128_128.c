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
typedef  unsigned int pcg128_t ;

/* Variables and functions */
 unsigned int PCG_128BIT_CONSTANT (unsigned long long,unsigned long long) ; 

inline pcg128_t pcg_output_rxs_m_xs_128_128(pcg128_t state) {
  pcg128_t word =
      ((state >> ((state >> 122u) + 6u)) ^ state) *
      (PCG_128BIT_CONSTANT(17766728186571221404ULL, 12605985483714917081ULL));
  // 327738287884841127335028083622016905945
  return (word >> 86u) ^ word;
}
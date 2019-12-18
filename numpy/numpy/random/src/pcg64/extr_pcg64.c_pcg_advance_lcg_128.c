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
typedef  int pcg128_t ;

/* Variables and functions */

pcg128_t pcg_advance_lcg_128(pcg128_t state, pcg128_t delta, pcg128_t cur_mult,
                             pcg128_t cur_plus) {
  pcg128_t acc_mult = 1u;
  pcg128_t acc_plus = 0u;
  while (delta > 0) {
    if (delta & 1) {
      acc_mult *= cur_mult;
      acc_plus = acc_plus * cur_mult + cur_plus;
    }
    cur_plus = (cur_mult + 1) * cur_plus;
    cur_mult *= cur_mult;
    delta /= 2;
  }
  return acc_mult * state + acc_plus;
}
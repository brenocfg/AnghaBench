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
typedef  unsigned int uint16_t ;

/* Variables and functions */

inline uint16_t pcg_output_rxs_m_xs_16_16(uint16_t state) {
  uint16_t word = ((state >> ((state >> 13u) + 3u)) ^ state) * 62169u;
  return (word >> 11u) ^ word;
}
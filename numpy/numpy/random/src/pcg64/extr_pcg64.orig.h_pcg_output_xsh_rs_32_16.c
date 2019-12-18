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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

inline uint16_t pcg_output_xsh_rs_32_16(uint32_t state) {
  return (uint16_t)(((state >> 11u) ^ state) >> ((state >> 30u) + 11u));
}
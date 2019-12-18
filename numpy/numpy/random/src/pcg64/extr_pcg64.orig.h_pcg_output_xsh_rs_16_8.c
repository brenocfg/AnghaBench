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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;

/* Variables and functions */

inline uint8_t pcg_output_xsh_rs_16_8(uint16_t state) {
  return (uint8_t)(((state >> 7u) ^ state) >> ((state >> 14u) + 3u));
}
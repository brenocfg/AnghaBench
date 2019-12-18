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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t Extract(uint32_t max_value, const uint8_t data[], size_t size,
                        uint32_t* const bit_pos) {
  uint32_t v = 0;
  int range = 1;
  while (*bit_pos < 8 * size && range <= max_value) {
    const uint8_t mask = 1u << (*bit_pos & 7);
    v = (v << 1) | !!(data[*bit_pos >> 3] & mask);
    range <<= 1;
    ++*bit_pos;
  }
  return v % (max_value + 1);
}
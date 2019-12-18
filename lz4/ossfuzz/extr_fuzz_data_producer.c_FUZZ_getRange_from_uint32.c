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

/* Variables and functions */

uint32_t FUZZ_getRange_from_uint32(uint32_t seed, uint32_t min, uint32_t max)
{
    uint32_t range = max - min;
    if (range == 0xffffffff) {
      return seed;
    }
    return min + seed % (range + 1);
}
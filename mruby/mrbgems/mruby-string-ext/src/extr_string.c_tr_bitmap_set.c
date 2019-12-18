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

/* Variables and functions */

__attribute__((used)) static inline void
tr_bitmap_set(uint8_t bitmap[32], uint8_t ch)
{
  uint8_t idx1 = ch / 8;
  uint8_t idx2 = ch % 8;
  bitmap[idx1] |= (1<<idx2);
}
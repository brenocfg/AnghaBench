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

/* Variables and functions */
 int* Special_Endings_bits ; 

__attribute__((used)) static int is_special_end(unsigned c) {
  return (c < 0x80) && (Special_Endings_bits[c >> 5] & (1 << (31 - (c & 31))));
}
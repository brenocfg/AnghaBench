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

__attribute__((used)) static uint32_t findGCD(uint32_t n1, uint32_t n2) {
  uint32_t n3;
  while (n2 != 0) {
    n3 = n1;
    n1 = n2;
    n2 = n3 % n2;
  }
  return n1;
}
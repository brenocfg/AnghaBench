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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t div1m(uint64_t n) {
  uint64_t q1 = (n >> 5) + (n >> 10);
  uint64_t q2 = (n >> 12) + (q1 >> 1);
  uint64_t q3 = (q2 >> 11) - (q2 >> 23);

  uint64_t q = n + q1 + q2 - q3;

  q = q >> 20;

  // Ignore the error term -- it is measured in pico seconds
  return q;
}
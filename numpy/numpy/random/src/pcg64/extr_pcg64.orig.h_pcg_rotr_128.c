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
typedef  unsigned int pcg128_t ;

/* Variables and functions */

inline pcg128_t pcg_rotr_128(pcg128_t value, unsigned int rot) {
  return (value >> rot) | (value << ((-rot) & 127));
}
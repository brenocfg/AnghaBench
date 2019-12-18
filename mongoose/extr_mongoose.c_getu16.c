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
typedef  int const uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t getu16(const char *p) {
  const uint8_t *up = (const uint8_t *) p;
  return (up[0] << 8) + up[1];
}
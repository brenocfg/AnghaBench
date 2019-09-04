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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_bigendian () ; 

uint32_t read_uint32(const unsigned char *c, const int pt) {
  uint32_t ui;
  char *p = (char *) &ui;

  if (!is_bigendian()) {  // le -> le (don't swap)
    p[0] = c[pt + 0];
    p[1] = c[pt + 1];
    p[2] = c[pt + 2];
    p[3] = c[pt + 3];
  } else {
    p[0] = c[pt + 3];
    p[1] = c[pt + 2];
    p[2] = c[pt + 1];
    p[3] = c[pt + 0];
  }
  return ui;
}
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

void write_uint32(unsigned char *buf, uint32_t ui) {
  if (!is_bigendian()) {  // le -> le (don't swap)
    buf[0] = ((unsigned char *) &ui)[0];
    buf[1] = ((unsigned char *) &ui)[1];
    buf[2] = ((unsigned char *) &ui)[2];
    buf[3] = ((unsigned char *) &ui)[3];
  } else {
    buf[0] = ((unsigned char *) &ui)[3];
    buf[1] = ((unsigned char *) &ui)[2];
    buf[2] = ((unsigned char *) &ui)[1];
    buf[3] = ((unsigned char *) &ui)[0];
  }
}
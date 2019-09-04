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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */

unsigned int coap_encode_var_bytes(unsigned char *buf, unsigned int val) {
  unsigned int n, i;

  for (n = 0, i = val; i && n < sizeof(val); ++n)
    i >>= 8;

  i = n;
  while (i--) {
    buf[i] = val & 0xff;
    val >>= 8;
  }

  return n;
}
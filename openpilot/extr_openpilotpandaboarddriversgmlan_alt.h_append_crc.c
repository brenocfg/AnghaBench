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

int append_crc(char *in, int in_len) {
  int crc = 0;
  for (int i = 0; i < in_len; i++) {
    crc <<= 1;
    if (in[i] ^ ((crc>>15)&1)) {
      crc = crc ^ 0x4599;
    }
    crc &= 0x7fff;
  }
  for (int i = 14; i >= 0; i--) {
    in[in_len++] = (crc>>i)&1;
  }
  return in_len;
}
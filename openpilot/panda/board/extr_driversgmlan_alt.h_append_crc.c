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
  unsigned int crc = 0;
  for (int i = 0; i < in_len; i++) {
    crc <<= 1;
    if (((unsigned int)(in[i]) ^ ((crc >> 15) & 1U)) != 0U) {
      crc = crc ^ 0x4599U;
    }
    crc &= 0x7fffU;
  }
  int in_len_copy = in_len;
  for (int i = 14; i >= 0; i--) {
    in[in_len_copy] = (crc >> (unsigned int)(i)) & 1U;
    in_len_copy++;
  }
  return in_len_copy;
}
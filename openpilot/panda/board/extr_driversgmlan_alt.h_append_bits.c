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

int append_bits(char *in, int in_len, char *app, int app_len) {
  int in_len_copy = in_len;
  for (int i = 0; i < app_len; i++) {
    in[in_len_copy] = app[i];
    in_len_copy++;
  }
  return in_len_copy;
}
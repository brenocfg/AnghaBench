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
typedef  scalar_t__ val ;

/* Variables and functions */

int append_int(char *in, int in_len, int val, int val_len) {
  int in_len_copy = in_len;
  for (int i = val_len - 1; i >= 0; i--) {
    in[in_len_copy] = ((unsigned int)(val) & (1U << (unsigned int)(i))) != 0U;
    in_len_copy++;
  }
  return in_len_copy;
}
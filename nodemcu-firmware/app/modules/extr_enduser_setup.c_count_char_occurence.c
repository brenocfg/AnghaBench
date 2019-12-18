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

__attribute__((used)) static int count_char_occurence(const char *input, const char char_to_count) {
  const char *current = input;
  int occur = 0;
    while (*current != 0) {
        if (*current == char_to_count) occur++;
    current++;
  }
  return occur;
}
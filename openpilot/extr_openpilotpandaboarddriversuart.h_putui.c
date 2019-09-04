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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  puts (char*) ; 

void putui(uint32_t i) {
  char str[11];
  uint8_t idx = 10;
  str[idx--] = '\0';
  do {
    str[idx--] = (i % 10) + 0x30;
    i /= 10;
  } while (i);
  puts(str + idx + 1);
}
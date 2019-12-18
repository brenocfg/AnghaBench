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
 int /*<<< orphan*/  putch (char) ; 

void puth(unsigned int i) {
  char c[] = "0123456789abcdef";
  for (int pos = 28; pos != -4; pos -= 4) {
    putch(c[(i >> (unsigned int)(pos)) & 0xFU]);
  }
}
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
 int SEGGER_RTT_Read (int /*<<< orphan*/ ,char*,int) ; 

int SEGGER_RTT_GetKey(void) {
  char c;
  int r;

  r = SEGGER_RTT_Read(0, &c, 1);
  if (r == 1) {
    return (int)(unsigned char)c;
  }
  return -1;
}
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
 short GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_CAPITAL ; 
 int /*<<< orphan*/  VK_NUMLOCK ; 
 int /*<<< orphan*/  VK_SCROLL ; 

int
mi_read_keyboard_state(void)
{
  short keydata;
  int code;

  code = 0;
  keydata = GetKeyState(VK_SCROLL);
  if (keydata & 0x0001)
  {
    code |= 1;
  }
  keydata = GetKeyState(VK_NUMLOCK);
  if (keydata & 0x0001)
  {
    code |= 2;
  }
  keydata = GetKeyState(VK_CAPITAL);
  if (keydata & 0x0001)
  {
    code |= 4;
  }
  return code;
}
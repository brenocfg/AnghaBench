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
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chrysler_camera_detected ; 

__attribute__((used)) static int chrysler_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;
  int addr = GET_ADDR(to_fwd);
  // forward CAN 0 -> 2 so stock LKAS camera sees messages
  if ((bus_num == 0) && !chrysler_camera_detected) {
    bus_fwd = 2;
  }
  // forward all messages from camera except LKAS_COMMAND and LKAS_HUD
  if ((bus_num == 2) && !chrysler_camera_detected && (addr != 658) && (addr != 678)) {
    bus_fwd = 0;
  }
  return bus_fwd;
}
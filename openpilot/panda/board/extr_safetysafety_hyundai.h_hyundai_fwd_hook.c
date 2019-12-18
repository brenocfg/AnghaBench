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
 int hyundai_camera_bus ; 
 scalar_t__ hyundai_giraffe_switch_2 ; 

__attribute__((used)) static int hyundai_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;
  // forward cam to ccan and viceversa, except lkas cmd
  if (hyundai_giraffe_switch_2) {
    if (bus_num == 0) {
      bus_fwd = hyundai_camera_bus;
    }
    if (bus_num == hyundai_camera_bus) {
      int addr = GET_ADDR(to_fwd);
      if (addr != 832) {
        bus_fwd = 0;
      }
    }
  }
  return bus_fwd;
}
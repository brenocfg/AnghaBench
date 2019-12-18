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
 int MAZDA_CAM ; 
 int MAZDA_LANEINFO ; 
 int MAZDA_LKAS ; 
 int MAZDA_MAIN ; 
 scalar_t__ mazda_forward_cam ; 
 int /*<<< orphan*/  mazda_giraffe_switch_2_on ; 
 scalar_t__ mazda_op_laneinfo_detected ; 
 scalar_t__ mazda_op_lkas_detected ; 

__attribute__((used)) static int mazda_fwd_hook(int bus, CAN_FIFOMailBox_TypeDef *to_fwd) {
  int bus_fwd = -1;
  if (mazda_forward_cam && !mazda_giraffe_switch_2_on) {
    int addr = GET_ADDR(to_fwd);
    if (bus == MAZDA_MAIN) {
      bus_fwd = MAZDA_CAM;
    }
    else if (bus == MAZDA_CAM) {
      // drop stock CAM_LKAS and CAM_LANEINFI if OP is sending them
      if (!((addr == MAZDA_LKAS) && mazda_op_lkas_detected) &&
          !((addr == MAZDA_LANEINFO) && mazda_op_laneinfo_detected)) {
	bus_fwd = MAZDA_MAIN;
      }
    }
    else {
      bus_fwd = -1;
    }
  }
  return bus_fwd;
}